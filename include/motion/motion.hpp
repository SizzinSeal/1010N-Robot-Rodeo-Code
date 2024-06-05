#pragma once

#include "units/Pose.hpp"
#include "units/units.hpp"

/**
 * @struct DifferentialChassisSpeeds
 *
 * @brief represents the left and right velocity of the drivetrain, or the left and right power percentage of the
 * drivetrain
 */
struct ChassisSpeeds {
        bool velocity = false; /** whether the requested response from the drivetrain should use voltage controllers or
                                  velocity controllers */
        LinearVelocity leftVelocity; /** left drive linear velocity */
        LinearVelocity rightVelocity; /** right drive linear velocity */
        double leftPwr; /** left drive percentage */
        double rightPwr; /** right drive percentage */
};

/**
 * @class DifferentialMotion
 *
 * @brief Abstract class which represents a motion algorithm for a differential drive robot
 *
 * We use this abstraction to allow for different motion algorithms to be used with the same interface.
 * This allows us to easily create and maintain motion algorithms while also allowing the user to
 * make custom motion algorithms without having to recompile the library.
 */
class Motion {
    public:
        /**
         * @brief Construct a new Differential Motion object
         *
         * The parameters are used to calculate the linear and angular velocity of the robot
         * as well as to modify the output speeds to prevent the motors from becoming saturated
         *
         * @param maxDriveVelocity the maximum theoretical velocity of the robot. Default is 0
         * @param desaturateBias the weight to determine whether to prioritize linear or angular velocity. 0 fully
         * prioritizes linear velocity, 1 fully prioritizes angular velocity. Default is 0.5
         */
        Motion(const LinearVelocity maxDriveVelocity = 0, const float desaturateBias = 0.5);
        /**
         * @brief Calculates the speed of the left and right wheels of a differential drive robot
         *
         * @param pose the current pose of the robot
         * @return DifferentialChassisSpeeds the speed of the left and right wheels
         */
        virtual ChassisSpeeds update(units::Pose pose) = 0;
        /**
         * @brief Get whether the motion is running
         *
         * @return true the motion is running
         * @return false the motion is not running
         */
        bool isRunning() const;
        /**
         * @brief Destroy the Differential Motion object
         *
         */
        virtual ~Motion();
    protected:
        bool running = true; /** whether the motion is running or not */
        const LinearVelocity maxDriveVelocity; /** the maximum velocity of the robot */
        float desaturateBias; /** weight to determine whether to prioritize linear or angular velocity when
                               desaturating the motors */
        /**
         * @brief Desaturates the motor speeds to prevent the motors from saturating
         *
         * @param speeds the speeds to desaturate
         * @return DifferentialChassisSpeeds
         */
        ChassisSpeeds desaturate(ChassisSpeeds speeds) const;
};