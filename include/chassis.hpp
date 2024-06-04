#pragma once

#include "controller/controller.hpp"
#include "motion/motion.hpp"
#include "odometry/odometry.hpp"
#include "pros/motor_group.hpp"
#include <memory>

class Chassis {
    private:
        const std::shared_ptr<pros::MotorGroup> leftDrive;
        const std::shared_ptr<pros::MotorGroup> rightDrive;
        const std::unique_ptr<Odometry> odometry;
        const std::unique_ptr < Controller
};