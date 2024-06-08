#include "chassis.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"

double avg(std::vector<double> vec) {
    if (vec.empty()) return 0;
    double sum = 0;
    for (const double& val : vec) sum += val;
    return sum / vec.size();
}

Chassis::Chassis(const std::shared_ptr<pros::MotorGroup> leftDrive, const std::shared_ptr<pros::MotorGroup> rightDrive,
                 const std::shared_ptr<Odometry> odometry, const Length trackWidth,
                 const std::shared_ptr<Controller<VelocityControllerInput, double>> leftVelocityController,
                 const std::shared_ptr<Controller<VelocityControllerInput, double>> rightVelocityController,
                 const std::shared_ptr<Controller<double, double>> linearPositionController,
                 const std::shared_ptr<Controller<double, double>> angularPositionController)
    : leftDrive(leftDrive),
      rightDrive(rightDrive),
      odometry(odometry),
      trackWidth(trackWidth),
      leftVelocityController(leftVelocityController),
      rightVelocityController(rightVelocityController),
      linearPositionController(linearPositionController),
      angularPositionController(angularPositionController) {}

void Chassis::initialize() {
    odometry->calibrate(); // calibrate odometry
    // reset the velocity controllers
    leftVelocityController->reset();
    rightVelocityController->reset();
    // start the chassis task, but only if it hasn't been started yet
    if (task == std::nullopt)
        task = pros::Task {[this]() {
            while (true) {
                this->update();
                pros::delay(10);
            }
        }};
}

void Chassis::move(std::unique_ptr<Motion> motion) {
    // wait for the previous motion to finish
    while (motion != nullptr) pros::delay(10);
    // reset position controllers
    linearPositionController->reset();
    angularPositionController->reset();
    // reset velocity controllers
    leftVelocityController->reset();
    rightVelocityController->reset();
    // set the competition state at the start of the motion
    prevCompState = pros::c::competition_get_status();
    // set the new motion
    this->motion = std::move(motion);
}

void Chassis::stopMotion() {
    motion.reset(); // delete the motion
    moveMotors(0, 0); // stop the motors
}

void Chassis::moveMotors(int left, int right) {
    leftDrive->move(left);
    rightDrive->move(right);
}

void Chassis::moveMotors(std::pair<int, int> powers) {
    leftDrive->move(powers.first);
    rightDrive->move(powers.second);
}

units::Pose Chassis::getPose() { return odometry->getPose(); }

void Chassis::setPose(units::Pose pose) { odometry->setPose(pose); }

void Chassis::update() {
    // update odometry
    const units::Pose pose = odometry->update();
    // update motion
    if (motion != nullptr) {
        // stop the motion if needed
        if (!motion->isRunning() || pros::competition::get_status() != prevCompState) {
            stopMotion();
            return;
        }
        const ChassisSpeeds speeds = motion->update(pose);
        // update velocity controllers if needed, reset otherwise and use open loop control
        if (speeds.velocity) {
            const double leftOut =
                leftVelocityController->update({speeds.leftVelocity.val(), avg(leftDrive->get_actual_velocity_all())});
            const double rightOut = rightVelocityController->update(
                {speeds.rightVelocity.val(), avg(rightDrive->get_actual_velocity_all())});
            leftDrive->move(leftOut);
            rightDrive->move(rightOut);
        } else {
            leftDrive->move(speeds.leftPwr * 127);
            rightDrive->move(speeds.rightPwr * 127);
        }
    }
}