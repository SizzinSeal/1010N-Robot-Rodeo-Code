#pragma once

#include "units/Pose.hpp"

class Odometry {
    public:
        virtual units::Pose update() = 0;
};
