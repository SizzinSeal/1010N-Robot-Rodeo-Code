#include "odometry/perpWheelOdom.hpp"
#include "hardware/imu/imu.hpp"
#include "pros/rtos.hpp"
#include "pros/misc.h"
#include <iostream>

/**
 * @brief calculate the chord length of an arc traveled by the robot given the delta length, offset, and delta angle
 *
 * @param deltaLength the change in length measured by the tracking wheel
 * @param offset the offset of the tracking wheel
 * @param deltaAngle the change in angle measured by the IMU
 * @return Length the chord length of the arc traveled by the robot
 */
Length calculateChord(Length deltaLength, Length offset, Angle deltaAngle) {
    if (deltaAngle == 0_stRad) return deltaLength; // prevent divide by 0
    const Length radius = offset + Length((deltaLength / deltaAngle).val());
    return 2 * radius * units::sin(deltaAngle / 2);
}

PerpWheelOdom::PerpWheelOdom(std::shared_ptr<TrackingWheel> verticalWheel,
                             std::shared_ptr<TrackingWheel> horizontalWheel, std::shared_ptr<IMU> imu)
    : verticalWheel(verticalWheel),
      horizontalWheel(horizontalWheel),
      imu(imu) {}

void PerpWheelOdom::calibrate() {
    // reset the tracking wheels and the IMU
    verticalWheel->reset();
    if (horizontalWheel != nullptr) horizontalWheel->reset();
    // calibrate IMU
    for (int i = 0; i < 5; i++) {
        while (imu->getStatus() == IMU_CALIBRATING) pros::delay(10);
        if (imu->getStatus() >= IMU_UNKOWN_ERROR) { std::cout << "IMU calibration failed! Try #" << i << std::endl; }
        if (imu->getStatus() == IMU_CALIBRATED) break;
        if (i == 4) pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, "---");
    }
    // reset the pose
    pose = {0_m, 0_m, 0_cRad};
    // reset the previous values
    prevVertical = std::nullopt;
    prevHorizontal = std::nullopt;
    prevAngle = std::nullopt;
}

void PerpWheelOdom::setPose(units::Pose pose) {
    this->pose = pose;
    imu->setYaw(pose.getTheta());
}

units::Pose PerpWheelOdom::update() {
    // get the distance traveled by the tracking wheels and the angle rotated by the IMU
    const Length vertical = verticalWheel->getDistance();
    // if horizontalWheel is nullptr, set horizontal to 0_m, otherwise set it to the distance traveled by the
    // horizontal wheel
    const Length horizontal = (horizontalWheel == nullptr) ? 0_m : horizontalWheel->getDistance();
    const Angle angle = imu->getRotation();
    // set previous values to the current values if they are not set
    // this should only happen on the first iteration
    if (prevVertical == std::nullopt) prevVertical = vertical;
    if (prevHorizontal == std::nullopt) prevHorizontal = horizontal;
    if (prevAngle == std::nullopt) prevAngle = angle;
    // calculate deltas
    const Length deltaVertical = vertical - prevVertical.value();
    const Length deltaHorizontal = horizontal - prevHorizontal.value();
    const Angle deltaAngle = angle - prevAngle.value();
    // calculate average angle
    const Angle avgAngle = prevAngle.value() + deltaAngle / 2;
    // update previous values
    prevVertical = vertical;
    prevHorizontal = horizontal;
    prevAngle = angle;
    // calculate local coordinates
    const Length localX = calculateChord(deltaHorizontal, horizontalWheel->getOffset(), deltaAngle);
    const Length localY = calculateChord(deltaVertical, verticalWheel->getOffset(), deltaAngle);
    units::Pose localPose(localX, localY);
    // rotate the local coordinates by the average angle to get the change in global coordinates
    localPose.rotateBy(avgAngle);
    // add the change in global coordinates to the current pose
    pose += localPose;
    // set the global heading
    pose.setTheta(angle);
    return pose;
}