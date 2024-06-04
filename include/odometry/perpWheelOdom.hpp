#pragma once

#include "odometry/odometry.hpp"
#include "hardware/trackingWheel.hpp"
#include "hardware/imu/imu.hpp"
#include <optional>

/**
 * @brief Odometry implementation using two perpendicular tracking wheels and an IMU
 *
 * This class uses two perpendicular tracking wheels and an IMU to calculate the robot's pose.
 */
class PerpWheelOdom : public Odometry {
    public:
        /**
         * @brief Construct a new PerpWheelOdom object
         *
         * @param verticalWheel unique pointer to the vertical tracking wheel
         * @param horizontalWheel unique pointer to the horizontal tracking wheel. Set to nullptr if there is no
         * horizontal tracking wheel
         * @param imu unique pointer to the IMU
         */
        PerpWheelOdom(std::unique_ptr<TrackingWheel> verticalWheel, std::unique_ptr<TrackingWheel> horizontalWheel,
                      std::unique_ptr<IMU> imu);
        /**
         * @brief Update the robot's pose
         *
         * @return units::Pose
         */
        units::Pose update() override;
    private:
        const std::unique_ptr<TrackingWheel> verticalWheel;
        const std::unique_ptr<TrackingWheel> horizontalWheel;
        const std::unique_ptr<IMU> imu;
        std::optional<Length> prevVertical;
        std::optional<Length> prevHorizontal;
        std::optional<Angle> prevAngle;
        units::Pose pose;
};