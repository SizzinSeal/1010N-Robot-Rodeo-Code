#include "motion/motion.hpp"
#include "units/units.hpp"

Motion::Motion(const LinearVelocity maxDriveVelocity, const float desaturateBias)
    : maxDriveVelocity(maxDriveVelocity),
      desaturateBias(desaturateBias) {}

bool Motion::isRunning() const { return running; }

ChassisSpeeds Motion::desaturate(ChassisSpeeds speeds) const {
    if (speeds.velocity) {
        LinearVelocity throttle = (speeds.rightVelocity - speeds.leftVelocity) / 2;
        // we don't calculate the angular velocity, instead we calculate the angular velocity of the robot multiplied by
        // the track width which cancels out the track width in the equation to get the angular velocity of the robot
        LinearVelocity turn = speeds.rightVelocity - throttle;
        if (units::abs(throttle) + units::abs(turn) > maxDriveVelocity) {
            const LinearVelocity oldThrottle = throttle;
            throttle *= 1 - desaturateBias * units::abs(turn / maxDriveVelocity).val();
            turn *= desaturateBias * units::abs(oldThrottle / maxDriveVelocity).val();
        }
        return {true, throttle, turn, 0, 0};
    } else {
        double throttle = (speeds.leftPwr - speeds.rightPwr) / 2;
        double turn = speeds.rightPwr - throttle;
        if (std::fabs(throttle) + std::fabs(turn) > 1) {
            const double oldThrottle = throttle;
            throttle *= 1 - desaturateBias * std::fabs(turn);
            turn *= desaturateBias * std::fabs(oldThrottle);
        }
        return {false, 0, 0, throttle, turn};
    }
}

Motion::~Motion() {}
