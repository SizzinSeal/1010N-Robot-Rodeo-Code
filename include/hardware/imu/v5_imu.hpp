#pragma once

#include "hardware/imu/imu.hpp"
#include "pros/imu.hpp"

class V5IMU : public IMU {
    public:
        /**
         * @brief Construct a new V5IMU object
         *
         * @param port the port the IMU is connected to
         */
        V5IMU(int port);
        /**
         * @brief Construct a new V5IMU object
         *
         * @param imu pointer to a PROS IMU
         */
        V5IMU(pros::Imu* imu);
        /**
         * @brief Calibrate the IMU, non-blocking
         *
         */
        virtual void calibrate() override;
        /**
         * @brief Get the Status of the IMU
         *
         * @return int see #IMUStatus for possible return values
         */
        virtual int getStatus() override;
        /**
         * @brief Get the rotation measured by the IMU
         *
         * This function returns the unbounded yaw measured by the IMU.
         * This means that the yaw can be any number of rotations.
         *
         * @return Angle
         */
        virtual Angle getRotation() override;
        /**
         * @brief Get the yaw measured by the IMU
         *
         * This function returns the yaw measured by the IMU.
         * The yaw is bounded between -0.5 and 0.5 rotations.
         *
         * @return Angle
         */
        virtual Angle getYaw() override;
        /**
         * @brief Set the yaw of the IMU
         *
         * @param angle the new yaw
         */
        virtual void setYaw(Angle angle) override;
        /**
         * @brief Get the pitch measured by the IMU
         *
         * @return Angle
         */
        virtual Angle getPitch() override;
        /**
         * @brief Set the pitch of the IMU
         *
         * @param angle the new pitch
         */
        virtual void setPitch(Angle angle) override;
        /**
         * @brief Get the roll measured by the IMU
         *
         * @return Angle
         */
        virtual Angle getRoll() override;
        /**
         * @brief Set the roll of the IMU
         *
         * @param angle the new roll
         */
        virtual void setRoll(Angle angle) override;
        /**
         * @brief Get the linear acceleration along the x axis
         *
         * @return LinearAcceleration
         */
        virtual LinearAcceleration getXAcceleration() override;
        /**
         * @brief Get the linear acceleration along the Y axis
         *
         * @return LinearAcceleration
         */
        virtual LinearAcceleration getYAcceleration() override;
        /**
         * @brief Get the linear acceleration along the Z axis
         *
         * @return LinearAcceleration
         */
        virtual LinearAcceleration getZAcceleration() override;
        /**
         * @brief Get the orientation of the IMU
         *
         * @return IMUOrientation
         */
        virtual IMUOrientation getOrientation() override;
    private:
        const std::unique_ptr<pros::Imu> imu; /** pointer to the PROS Imu*/
};
