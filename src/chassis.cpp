#include "chassis.hpp"

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
                 const std::shared_ptr<Controller<double, double>> angularPositionController,
                 const std::shared_ptr<Motion> motion)
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
    while (motion != nullptr) { pros::delay(10); }
    this->motion = std::move(motion);
}

void Chassis::update() {
    // update odometry
    const units::Pose pose = odometry->update();
    // update motion
    if (motion != nullptr) {
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
            leftVelocityController->reset();
            rightVelocityController->reset();
            leftDrive->move(speeds.leftPwr * 127);
            rightDrive->move(speeds.rightPwr * 127);
        }
    }
}