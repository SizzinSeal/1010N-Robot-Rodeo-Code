#pragma once

#include "controller/controller.hpp"
#include "motion/motion.hpp"
#include "odometry/odometry.hpp"
#include "pros/motor_group.hpp"
#include "pros/rtos.hpp"
#include <memory>

class Chassis {
    public:
        /**
         * @brief Construct a new Chassis object
         *
         * @param leftDrive shared ptr to the left drive motor group
         * @param rightDrive shared ptr to the right drive motor group
         * @param odometry shared ptr to the odometry object
         * @param linearVelocityController shared ptr to the linear velocity controller
         * @param angularVelocityController shared ptr to the angular velocity controller
         * @param linearPositionController shared ptr to the linear position controller
         * @param angularPositionController shared ptr to the angular position controller
         * @param motion shared ptr to the motion object
         */
        Chassis(const std::shared_ptr<pros::MotorGroup> leftDrive, const std::shared_ptr<pros::MotorGroup> rightDrive,
                const std::shared_ptr<Odometry> odometry,
                const std::shared_ptr<Controller<double, double>> linearVelocityController,
                const std::shared_ptr<Controller<double, double>> angularVelocityController,
                const std::shared_ptr<Controller<double, double>> linearPositionController,
                const std::shared_ptr<Controller<double, double>> angularPositionController,
                const std::shared_ptr<Motion> motion);
        /**
         * @brief initialize the chassis thread, and calibrate sensors
         *
         */
        void initialize();
        /**
         * @brief move the drive motors at a certain velocity
         *
         * @param leftVelocity left velocity
         * @param rightVelocity right velocity
         */
        void moveDrive(const LinearVelocity leftVelocity, const LinearVelocity rightVelocity);
        /**
         * @brief move the drive motors at a certain output percentage
         *
         * @param leftPwr left power, from -1 to 1
         * @param rightPwr right power, from -1 to 1
         */
        void moveDrive(const double leftPwr, const double rightPwr);
        /**
         * @brief move the chassis with a custom motion algorithm
         *
         * @param motion
         */
        void move(std::unique_ptr<Motion> motion);
    protected:
        /**
         * @brief update odometry and the motion algs
         *
         */
        void update();
        const std::shared_ptr<pros::MotorGroup> leftDrive;
        const std::shared_ptr<pros::MotorGroup> rightDrive;
        const std::shared_ptr<Odometry> odometry;
        const std::shared_ptr<Controller<double, double>> linearVelocityController;
        const std::shared_ptr<Controller<double, double>> angularVelocityController;
        const std::shared_ptr<Controller<double, double>> linearPositionController;
        const std::shared_ptr<Controller<double, double>> angularPositionController;
        std::unique_ptr<Motion> motion;
        std::optional<pros::Task> task;
};