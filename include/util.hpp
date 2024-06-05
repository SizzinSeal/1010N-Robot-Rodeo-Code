#pragma once

template <typename T> T sgn(T t) { return (t < 0) ? -1 : 1; }