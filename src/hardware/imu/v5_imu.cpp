#include "hardware/imu/v5_imu.hpp"
#include "pros/imu.h"
#include "units/Angle.hpp"
#include "units/units.hpp"

V5IMU::V5IMU(int port)
    : imu(std::make_unique<pros::Imu>(port)) {}

V5IMU::V5IMU(pros::Imu* imu)
    : imu(imu) {}

void V5IMU::calibrate() { imu->reset(); }

int V5IMU::getStatus() {
    const pros::ImuStatus status = imu->get_status();
    switch (status) {
        case pros::ImuStatus::calibrating: return IMUStatus::CALIBRATING;
        case pros::ImuStatus::ready: return IMUStatus::CALIBRATED;
        default: return IMUStatus::UNKOWN_ERROR;
    }
}

Angle V5IMU::getRotation() { return from_cdeg(imu->get_rotation()); }

Angle V5IMU::getYaw() { return from_cdeg(imu->get_yaw()); }

void V5IMU::setYaw(Angle angle) { imu->set_yaw(to_cDeg(angle)); }

Angle V5IMU::getPitch() { return from_cdeg(imu->get_pitch()); }

void V5IMU::setPitch(Angle angle) { imu->set_pitch(to_cDeg(angle)); }

Angle V5IMU::getRoll() { return from_cdeg(imu->get_roll()); }

void V5IMU::setRoll(Angle angle) { imu->set_roll(to_cDeg(angle)); }

LinearAcceleration V5IMU::getXAcceleration() { return (imu->get_accel().x); }

LinearAcceleration V5IMU::getYAcceleration() { return (imu->get_accel().y); }

LinearAcceleration V5IMU::getZAcceleration() { return (imu->get_accel().z); }

IMUOrientation V5IMU::getOrientation() {
    const pros::imu_orientation_e_t orientation = imu->get_physical_orientation();
    switch (orientation) {
        case pros::imu_orientation_e_t::E_IMU_X_UP: return IMUOrientation::X_UP;
        case pros::imu_orientation_e_t::E_IMU_X_DOWN: return IMUOrientation::X_DOWN;
        case pros::imu_orientation_e_t::E_IMU_Y_UP: return IMUOrientation::Y_UP;
        case pros::imu_orientation_e_t::E_IMU_Y_DOWN: return IMUOrientation::Y_DOWN;
        case pros::imu_orientation_e_t::E_IMU_Z_UP: return IMUOrientation::Z_UP;
        case pros::imu_orientation_e_t::E_IMU_Z_DOWN: return IMUOrientation::Z_DOWN;
        default: return IMUOrientation::Z_DOWN;
    }
}