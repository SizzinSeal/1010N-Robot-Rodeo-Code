#pragma once

/**
 * @brief get the sign of a number
 *
 * @tparam T the type of the input number
 * @param t the number to get the sign of
 * @return T
 */
template <typename T> T sgn(T t) { return (t < 0) ? -1 : 1; }
