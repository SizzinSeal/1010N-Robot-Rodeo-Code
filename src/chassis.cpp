#include "chassis.hpp"

Chassis::Chassis(const std::shared_ptr<pros::MotorGroup> leftDrive, const std::shared_ptr<pros::MotorGroup> rightDrive,
                 const std::shared_ptr<Odometry> odometry,
                 const std::shared_ptr<Controller<double, double>> linearVelocityController,
                 const std::shared_ptr<Controller<double, double>> angularVelocityController,
                 const std::shared_ptr<Controller<double, double>> linearPositionController,
                 const std::shared_ptr<Controller<double, double>> angularPositionController,
                 const std::shared_ptr<Motion> motion)
    : leftDrive(leftDrive),
      rightDrive(rightDrive),
      odometry(odometry),
      linearVelocityController(linearVelocityController),
      angularVelocityController(angularVelocityController),
      linearPositionController(linearPositionController),
      angularPositionController(angularPositionController) {}

void Chassis::initialize() {
    odometry->calibrate(); // calibrate odometry
    // start the chassis task, but only if it hasn't been started yet
    if (task == std::nullopt)
        task = pros::Task {[this]() {
            while (true) {
                update();
                pros::delay(10);
            }
        }};
}