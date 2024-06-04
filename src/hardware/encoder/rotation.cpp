#include "hardware/encoder/rotation.hpp"

Rotation::Rotation(pros::Rotation* sensor, float gearRatio)
    : sensor(sensor),
      gearRatio(gearRatio) {}

Rotation::Rotation(int port, float gearRatio)
    : sensor(std::make_unique<pros::Rotation>(port)),
      gearRatio(gearRatio) {}

void Rotation::calibrate() { sensor->reset_position(); }

int Rotation::getStatus() {
    if (sensor->is_installed()) return ENCODER_UNKNOWN_ERROR;
    else return ENCODER_CALIBRATED;
}

void Rotation::tare() { sensor->reset_position(); }

Angle Rotation::getPosition() {
    // divide get_position by 100 to convert from centidegrees to degrees
    // multiply by the gear ratio
    return from_sdeg(gearRatio * sensor->get_position() / 100.0);
}

void Rotation::setPosition(Angle angle) {
    // multiply get_angle by 100 to convert from degrees to centidegrees
    // divide by the gear ratio
    sensor->set_position(to_sDeg(angle) * 100 / gearRatio);
}

Angle Rotation::getAngle() {
    // divide get_angle by 100 to convert from centidegrees to degrees
    // multiply by the gear ratio
    return from_sdeg(sensor->get_angle() / 100.0);
}

bool Rotation::getReversed() { return sensor->get_reversed(); }

void Rotation::setReversed(bool reversed) { sensor->set_reversed(reversed); }

float Rotation::getGearRatio() { return gearRatio; }

void Rotation::setGearRatio(float gearRatio) { this->gearRatio = gearRatio; }