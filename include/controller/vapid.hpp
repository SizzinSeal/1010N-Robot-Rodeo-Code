#pragma once

#include "controller/controller.hpp"
#include "timer.hpp"
#include <optional>

/**
 * @brief input struct for the VAPID controller
 *
 */
struct VelocityControllerInput {
        const double targetAcceleration;
        const double targetVelocity;
        const double currentVelocity;
};

/**
 * @brief VAPID class. This is a velocity controller that uses a PID controller with acceleration and velocity
 * feedforward.
 *
 */
class VAPID : public Controller<VelocityControllerInput, double> {
    public:
        /**
         * @brief Construct a new VAPID object
         *
         * @param kV velocity feedforward gain
         * @param kA acceleration feedforward gain
         * @param kP proportional feedback gain
         * @param kI integral feedback gain
         * @param kD derivative feedback gain
         */
        VAPID(double kV, double kA, double kP, double kI, double kD);
        /**
         * @brief update the controller
         *
         * @param input the input to the controller
         * @return double the output of the controller
         */
        double update(VelocityControllerInput input) override;
        /**
         * @brief reset any persistent state in the controller
         *
         */
        void reset() override;
        /**
         * @brief Set the gains of the controller
         *
         * @param kV velocity feedforward gain
         * @param kA acceleration feedforward gain
         * @param kP proportional feedback gain
         * @param kI integral feedback gain
         * @param kD derivative feedback gain
         */
        void setGains(double kV, double kA, double kP, double kI, double kD);
    private:
        std::optional<Timer> timer; /** timer for calculating derivative and integral */
        std::optional<uint32_t> lastTime; /** last time the controller was updated */
        double integral = 0; /** integral value of the controller */
        std::optional<double> lastError = 0; /** last error of the controller */
        double kV; /** velocity feedforward gain */
        double kA; /** acceleration feedforward gain */
        double kP; /** proportional feedback gain */
        double kI; /** integral feedback gain */
        double kD; /** derivative feedback gain */
};