#pragma once

#include "units/Pose.hpp"

class Odometry {
    public:
        Odometry(units::Pose pose = {0_m, 0_m, 0_cRad});
        virtual void calibrate() = 0;
        virtual units::Pose update() = 0;
        units::Pose getPose();
        virtual void setPose(units::Pose pose);
        virtual ~Odometry();
    protected:
        units::Pose pose;
};
