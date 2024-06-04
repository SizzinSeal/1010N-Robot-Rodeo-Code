#pragma once

#include "odometry/odometry.hpp"
#include "hardware/trackingWheel.hpp"
#include "hardware/imu/imu.hpp"

/**
 * @brief
 *
 */
class TrackingWheelOdom : public Odometry {
    public:
        TrackingWheelOdom(std::unique_ptr<TrackingWheel> verticalWheel, std::unique_ptr<TrackingWheel> horizontalWheel,
                          std::unique_ptr<IMU> imu);
        units::Pose update() override;
    private:
        const std::unique_ptr<TrackingWheel> verticalWheel;
        const std::unique_ptr<TrackingWheel> horizontalWheel;
        const std::unique_ptr<IMU> imu;
        units::Pose pose;
};