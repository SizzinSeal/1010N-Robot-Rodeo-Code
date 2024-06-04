#include "odometry/perpWheelOdom.hpp"

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

PerpWheelOdom::PerpWheelOdom(std::unique_ptr<TrackingWheel> verticalWheel,
                             std::unique_ptr<TrackingWheel> horizontalWheel, std::unique_ptr<IMU> imu)
    : verticalWheel(std::move(verticalWheel)),
      horizontalWheel(std::move(horizontalWheel)),
      imu(std::move(imu)) {}

units::Pose PerpWheelOdom::update() {
    // get the distance traveled by the tracking wheels and the angle rotated by the IMU
    const Length vertical = verticalWheel->getDistance();
    // if horizontalWheel is nullptr, set horizontal to 0_m, otherwise set it to the distance traveled by the horizontal
    // wheel
    const Length horizontal = (horizontalWheel == nullptr) ? 0_m : horizontalWheel->getDistance();
    const Angle angle = imu->getRotation();
    // set previous values to the current values if they are not set
    // this should only happen on the first iteration
    if (prevVertical == std::nullopt) prevVertical = vertical;
    if (prevHorizontal == std::nullopt) prevHorizontal = horizontal;
    if (prevAngle == std::nullopt) prevAngle = angle;
    // calculate deltas
    const Length deltaVertical = vertical - *prevVertical;
    const Length deltaHorizontal = horizontal - *prevHorizontal;
    const Angle deltaAngle = angle - *prevAngle;
    // calculate average angle
    const Angle avgAngle = *prevAngle + deltaAngle / 2;
    // update previous values
    *prevVertical = vertical;
    *prevHorizontal = horizontal;
    *prevAngle = angle;
    // calculate local X and Y coordinates
    const Length localX = calculateChord(deltaHorizontal, horizontalWheel->getOffset(), deltaAngle);
    const Length localY = calculateChord(deltaVertical, verticalWheel->getOffset(), deltaAngle);
    units::V2Position localPose = {localX, localY};
    // rotate the local coordinates by the average angle to get the global coordinates
    pose = units::Pose(localPose.rotatedBy(avgAngle), angle);
    return pose;
}