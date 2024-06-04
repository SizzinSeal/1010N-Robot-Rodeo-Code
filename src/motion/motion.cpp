#include "motion/motion.hpp"
#include "units/units.hpp"

Motion::Motion(const Length trackWidth, const LinearVelocity maxDriveVelocity, const float desaturateBias)
    : trackWidth(trackWidth),
      maxDriveVelocity(maxDriveVelocity),
      desaturateBias(desaturateBias) {}

bool Motion::isRunning() const { return running; }

ChassisSpeeds Motion::desaturate(ChassisSpeeds speeds) const {}

Motion::~Motion() {}
