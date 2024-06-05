#include "opcontrol/arcade.hpp"
#include "util.hpp"
#include <cmath>

std::pair<int, int> arcade(int throttle, int turn, double desaturateBias, std::unique_ptr<DriveCurve> throttleCurve,
                           std::unique_ptr<DriveCurve> turnCurve) {
    // curve input
    throttle = std::round(throttleCurve->curve(throttle));
    turn = std::round(throttleCurve->curve(turn));
    // desaturate motors based on joyBias
    if (std::abs(throttle) + std::abs(turn) > 127) {
        const int oldThrottle = throttle;
        throttle *= (1 - desaturateBias * std::abs(turn / 127.0));
        turn *= desaturateBias * std::abs(oldThrottle / 127.0);
        // ensure the sum of the two values is equal to 127
        // this check is necessary because of integer division
        if (std::abs(turn) + std::abs(throttle) == 126) {
            if (desaturateBias < 0.5) throttle += sgn(throttle);
            else turn += sgn(turn);
        }
    }
    return std::make_pair(throttle + turn, throttle - turn);
}