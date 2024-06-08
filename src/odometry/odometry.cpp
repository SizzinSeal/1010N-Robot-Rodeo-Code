#include "odometry/odometry.hpp"

Odometry::Odometry(units::Pose pose)
    : pose(pose) {}

units::Pose Odometry::getPose() { return pose; }

void Odometry::setPose(units::Pose pose) { this->pose = pose; }

Odometry::~Odometry() {}
