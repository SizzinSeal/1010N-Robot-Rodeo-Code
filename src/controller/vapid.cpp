#include "controller/vapid.hpp"
#include "pros/rtos.hpp"

VAPID::VAPID(double kV, double kA, double kP, double kI, double kD)
    : kV(kV),
      kA(kA),
      kP(kP),
      kI(kI),
      kD(kD) {}

double VAPID::update(VelocityControllerInput input) {
    const double error = input.targetVelocity - input.currentVelocity;
    // initialize optional values
    if (lastError == std::nullopt) lastError = error;
    if (timer == std::nullopt) timer = Timer(UINT32_MAX);
    if (lastTime == std::nullopt) lastTime = pros::millis();
    const double dError = error - lastError.value();
    const int dt = timer->getTimePassed() - lastTime.value();
    const double derivative = (dt == 0) ? 0 : (error - lastError.value()) / dt;
    integral += dt * (lastError.value() + dError / 2);
    // update previous values
    lastError = error;
    lastTime = timer->getTimePassed();
    // return output
    return kV * input.targetVelocity + kA * input.targetAcceleration + kP * error + kI * integral + kD * derivative;
}