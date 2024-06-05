#pragma once

#include "controller/controller.hpp"
#include "motion/motion.hpp"
#include "odometry/odometry.hpp"
#include "pros/motor_group.hpp"
#include "pros/rtos.hpp"
#include <memory>

struct VelocityControllerInput {
        const double target;
        const double current;
};

class Chassis {
    public:
        /**
         * @brief Construct a new Chassis object
         *
         * @param leftDrive shared ptr to the left drive motor group
         * @param rightDrive shared ptr to the right drive motor group
         * @param odometry shared ptr to the odometry object
         * @param trackWidth the distance between the left and right wheels
         * @param leftVelocityController shared ptr to the linear velocity controller
         * @param rightVelocityController shared ptr to the angular velocity controller
         * @param linearPositionController shared ptr to the linear position controller
         * @param angularPositionController shared ptr to the angular position controller
         */
        Chassis(const std::shared_ptr<pros::MotorGroup> leftDrive, const std::shared_ptr<pros::MotorGroup> rightDrive,
                const std::shared_ptr<Odometry> odometry, const Length trackWidth,
                const std::shared_ptr<Controller<VelocityControllerInput, double>> leftVelocityController,
                const std::shared_ptr<Controller<VelocityControllerInput, double>> rightVelocityController,
                const std::shared_ptr<Controller<double, double>> linearPositionController,
                const std::shared_ptr<Controller<double, double>> angularPositionController);
        /**
         * @brief initialize the chassis thread, and calibrate sensors
         *
         */
        void initialize();
        /**
         * @brief move the chassis with a custom motion algorithm
         *
         * @param motion
         */
        void move(std::unique_ptr<Motion> motion);
        /**
         * @brief stop the current motion
         *
         */
        void stopMotion();
        /**
         * @brief move the left and right drive motors
         *
         * @param left left drive motor power (-127 to 127)
         * @param right right drive motor power (-127 to 127)
         */
        void moveMotors(int left, int right);
        /**
         * @brief move the left and right drive motors
         *
         * @param powers a pair of left and right drive motor powers (-127 to 127)
         */
        void moveMotors(std::pair<int, int> powers);
    protected:
        /**
         * @brief update odometry the motion alg, and velocity controllers
         *
         */
        void update();
        int prevCompState = -1;
        const Length trackWidth;
        // TODO: replace with LemLib motor abstraction
        const std::shared_ptr<pros::MotorGroup> leftDrive;
        const std::shared_ptr<pros::MotorGroup> rightDrive;
        const std::shared_ptr<Odometry> odometry;
        const std::shared_ptr<Controller<VelocityControllerInput, double>> leftVelocityController;
        const std::shared_ptr<Controller<VelocityControllerInput, double>> rightVelocityController;
        const std::shared_ptr<Controller<double, double>> linearPositionController;
        const std::shared_ptr<Controller<double, double>> angularPositionController;
        std::unique_ptr<Motion> motion;
        std::optional<pros::Task> task;
};