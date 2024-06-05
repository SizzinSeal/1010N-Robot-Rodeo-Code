#pragma once

#include "opcontrol/driveCurve.hpp"
#include <memory>
#include <utility>

/**
 * @brief arcade drive algorithm
 *
 * @param throttle requested throttle from -127 to 127
 * @param turn requested turn from -127 to 127
 * @param desaturateBias how much to favor angular motion over lateral motion or vice versa when motors are
 * saturated. A value of 0 fully prioritizes lateral motion, a value of 1 fully prioritizes angular motion
 * @param throttleCurve the curve to apply to the throttle input
 * @param turnCurve the curve to apply to the turn input
 * @return std::pair<int, int> the left and right motor powers, respectively
 */
std::pair<int, int> arcade(int throttle, int turn, double desaturateBias, std::unique_ptr<DriveCurve> throttleCurve,
                           std::unique_ptr<DriveCurve> turnCurve);
