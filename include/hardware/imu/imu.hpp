#pragma once

#include "units/Angle.hpp"

/**
 * @brief IMUStatus enum
 *
 * This enum is used to represent the status of a generic IMU (Inertial Measurement Unit)
 *
 * We use an enum instead of an enum class because implementations of this abstract class
 * may implement additional status codes that are not defined in this enum. We evaluate
 * the enum as an int in the getStatus() function. This way we can still check for the
 * status codes defined in the enum, and for additional status codes that are not defined
 * we can check if the status code is greater than the highest defined status code.
 */
enum IMUStatus { IMU_CALIBRATED = 0, IMU_CALIBRATING = 1, IMU_NOT_CALIBRATED = 2, IMU_UNKOWN_ERROR = 3 };

/**
 * @brief IMUOrientation enum
 *
 * This enum is used to represent the orientation of a generic IMU (Inertial Measurement Unit)
 */
enum class IMUOrientation { X_UP, X_DOWN, Y_UP, Y_DOWN, Z_UP, Z_DOWN };

/**
 * @class IMU
 *
 * @brief Abstract IMU (Inertial Measurement Unit) class
 */
class IMU {
    public:
        /**
         * @brief Calibrate the IMU, non-blocking
         *
         */
        virtual void calibrate() = 0;
        /**
         * @brief Get the Status of the IMU
         *
         * @return int see #IMUStatus for possible return values
         */
        virtual int getStatus() = 0;
        /**
         * @brief Get the rotation measured by the IMU
         *
         * This function returns the unbounded yaw measured by the IMU.
         * This means that the yaw can be any number of rotations.
         *
         * @return Angle
         */
        virtual Angle getRotation() = 0;
        /**
         * @brief Get the yaw measured by the IMU
         *
         * This function returns the yaw measured by the IMU.
         * The yaw is bounded between -0.5 and 0.5 rotations.
         *
         * @return Angle
         */
        virtual Angle getYaw() = 0;
        /**
         * @brief Set the yaw of the IMU
         *
         * @param angle the new yaw
         */
        virtual void setYaw(Angle angle) = 0;
        /**
         * @brief Get the pitch measured by the IMU
         *
         * @return Angle
         */
        virtual Angle getPitch() = 0;
        /**
         * @brief Set the pitch of the IMU
         *
         * @param angle the new pitch
         */
        virtual void setPitch(Angle angle) = 0;
        /**
         * @brief Get the roll measured by the IMU
         *
         * @return Angle
         */
        virtual Angle getRoll() = 0;
        /**
         * @brief Set the roll of the IMU
         *
         * @param angle the new roll
         */
        virtual void setRoll(Angle angle) = 0;
        /**
         * @brief Get the linear acceleration along the x axis
         *
         * @return LinearAcceleration
         */
        virtual LinearAcceleration getXAcceleration() = 0;
        /**
         * @brief Get the linear acceleration along the Y axis
         *
         * @return LinearAcceleration
         */
        virtual LinearAcceleration getYAcceleration() = 0;
        /**
         * @brief Get the linear acceleration along the Z axis
         *
         * @return LinearAcceleration
         */
        virtual LinearAcceleration getZAcceleration() = 0;
        /**
         * @brief Get the orientation of the IMU
         *
         * @return IMUOrientation
         */
        virtual IMUOrientation getOrientation() = 0;
        /**
         * @brief Destroy the IMU object
         *
         */
        virtual ~IMU();
};
