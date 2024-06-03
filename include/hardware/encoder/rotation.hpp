#pragma once

#include "hardware/encoder/encoder.hpp"
#include "pros/rotation.hpp"

/**
 * @brief V5Rotation Sensor class, inherits from Encoder
 *
 */
class Rotation : public Encoder {
    public:
        /**
         * @brief Construct a new Rotation object
         *
         * @param sensor pointer to a rotation sensor
         * @param gearRatio the gear ratio (teeth of driven gear / teeth of driving gear). Defaults to 1.0
         */
        Rotation(pros::Rotation* sensor, float gearRatio = 1.0);
        /**
         * @brief Construct a new Rotation object
         *
         * @param port the port of the rotation sensor. Use negative to reverse the sensor
         * @param gearRatio the gear ratio (teeth of driven gear / teeth of driving gear). Defaults to 1.0
         */
        Rotation(int port, float gearRatio = 1.0);
        /**
         * @brief calibrate the sensor
         *
         * This will zero the rotation sensor
         */
        void calibrate() override;
        /**
         * @brief Get the status of the encoder
         *
         * This function returns the status of the encoder. This can be used during calibration
         * to determine if the encoder is ready to be used. It returns an int instead of an enum
         * to allow implementations to add additional status codes if needed.
         * See #EncoderStatus for universal status codes.
         *
         * @return int
         */
        int getStatus() override;
        /**
         * @brief tare the sensor
         *
         * This will zero the rotation sensor
         */
        void tare() override;
        /**
         * @brief Get the unbounded angle measured by the encoder
         *
         * This function returns the unbounded angle measured by the encoder. This means
         * that the angle could be more than 1 rotation.
         *
         * @return Angle the angle measured by the encoder
         */
        Angle getPosition() override;
        /**
         * @brief Set the unbounded angle of the encoder
         *
         * This function returns the unbounded angle measured by the encoder. This means
         * that the angle could be more than 1 rotation.
         *
         * @param angle the angle to set the encoder to
         */
        void setPosition(Angle angle) override;
        /**
         * @brief Get the bounded angle measured by the encoder
         *
         * This function returns the bounded angle measured by the encoder. This means
         * that the angle is always between 0 and 1 rotations.
         *
         * @return Angle
         */
        Angle getAngle() override;
        /**
         * @brief get whether the encoder is reversed or not
         *
         * @return true the encoder is reversed
         * @return false the encoder is not reversed
         */
        bool getReversed() override;
        /**
         * @brief set whether the encoder should be reversed or not
         *
         * If the encoder is reversed from its previous state, the encoder should
         * invert the direction of the angle it returns. It does not only affect
         * subsequent changes to the encoder's angle, but previous angles as well.
         *
         * @param reversed whether the encoder should be reversed or not
         */
        void setReversed(bool reversed) override;
        /**
         * @brief Get the gear ratio of the encoder
         *
         * @return float teeth of driven gear / teeth of driving gear
         */
        float getGearRatio() override;
        /**
         * @brief Set the gear ratio of the encoder
         *
         * If the encoder's gear ratio is changed from its previous state, the encoder
         * will adjust the angle it returns to account for the new gear ratio. It does
         * not only affect subsequent changes to the encoder's angle, but previous angles
         * as well.
         *
         * @param gearRatio teeth of driven gear / teeth of driving gear
         */
        void setGearRatio(float gearRatio) override;
    private:
        const std::unique_ptr<pros::Rotation> sensor; /** unique ptr to the rotation sensor */
        float gearRatio; /** gear ratio. teeth of driven gear / teeth of driving gear */
};
