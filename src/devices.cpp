#include "devices.hpp"
#include "odometry/perpWheelOdom.hpp"
#include "hardware/encoder/rotation.hpp"
#include "hardware/imu/v5_imu.hpp"

// configure odometry
std::shared_ptr<Rotation> verticalEncoder = std::make_shared<Rotation>(5); // TODO: change port
std::shared_ptr<TrackingWheel> verticalWheel =
    std::make_shared<TrackingWheel>(verticalEncoder, 2.75_in, 0_in); // TODO: configure lengths
std::shared_ptr<Rotation> horizontalEncoder = std::make_shared<Rotation>(6); // TODO: change port
std::shared_ptr<TrackingWheel> horizontalWheel =
    std::make_shared<TrackingWheel>(horizontalEncoder, 2.75_in, 0_in); // TODO: configure lengths
std::shared_ptr<V5IMU> imu = std::make_shared<V5IMU>(7); // TODO: change port
std::shared_ptr<PerpWheelOdom> odometry = std::make_shared<PerpWheelOdom>(verticalWheel, horizontalWheel, imu);

// configure motors
std::shared_ptr<pros::MotorGroup> leftDrive(new pros::MotorGroup({1, 2})); // TODO: change ports
std::shared_ptr<pros::MotorGroup> rightDrive(new pros::MotorGroup({3, 4})); // TODO: change ports

// configure controllers
std::shared_ptr<Controller<VelocityControllerInput, double>> leftVelocityController; // TODO: implement vel controllers
std::shared_ptr<Controller<VelocityControllerInput, double>> rightVelocityController; // TODO: implement vel controllers
std::shared_ptr<Controller<double, double>> linearPositionController; // TODO: implement pos controllers
std::shared_ptr<Controller<double, double>> angularPositionController; // TODO: implement pos controllers

// configure chassis
Chassis chassis(leftDrive, rightDrive, odometry, 12_in, leftVelocityController, rightVelocityController,
                linearPositionController, angularPositionController);
