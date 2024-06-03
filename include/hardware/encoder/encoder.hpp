#pragma once

#include "units/Angle.hpp"

/**
 * @brief enum to represent the status of the encoder
 *
 * We use a regular enum instead  of an enum class because this allows implementations
 * of this abstract class to add additional status codes if needed.
 */
enum EncoderStatus {
    CALIBRATED = 0, /** the encoder has been calibrated and is ready to use */
    CALIBRATING = 1, /** the encoder is currently calibrating */
    NOT_CALIBRATED = 2, /** the encoder is not calibrated but is functioning */
    UNKNOWN_ERROR = 3 /** the encoder is not functioning */
};

/**
 * @brief Abstract encoder class
 *
 * This class is used to allow the user to define their own encoders to be used.
 * While we provide implementations for official VEX encoders, VEXU teams may want
 * to use custom encoders.
 */
class Encoder {
    public:
        /**
         * @brief Calibrate the encoder
         *
         * This function should be non-blocking and should return as fast as possible.
         * The angle read by the encoder may or may not change during calibration, behaviour
         * is implementation dependent.
         */
        virtual void calibrate() = 0;
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
        virtual int getStatus() = 0;
        /**
         * @brief tare the encoder
         *
         * This function is used to reset the encoder's measured angle to compass angle north.
         * This does not affect the encoder's calibration status, as it is analogous to calling
         * setAngle(0_cdeg)
         */
        virtual void tare() = 0;
        /**
         * @brief Get the unbounded angle measured by the encoder
         *
         * This function returns the unbounded angle measured by the encoder. This means
         * that the angle could be more than 1 rotation.
         *
         * @return Angle the angle measured by the encoder
         */
        virtual Angle getPosition() = 0;
        /**
         * @brief Set the unbounded angle of the encoder
         *
         * This function returns the unbounded angle measured by the encoder. This means
         * that the angle could be more than 1 rotation.
         *
         * @param angle the angle to set the encoder to
         */
        virtual void setPosition(Angle angle) = 0;
        /**
         * @brief Get the bounded angle measured by the encoder
         *
         * This function returns the bounded angle measured by the encoder. This means
         * that the angle is always between 0 and 1 rotations.
         *
         * @return Angle
         */
        virtual Angle getAngle() = 0;
        /**
         * @brief get whether the encoder is reversed or not
         *
         * @return true the encoder is reversed
         * @return false the encoder is not reversed
         */
        virtual bool getReversed() = 0;
        /**
         * @brief set whether the encoder should be reversed or not
         *
         * If the encoder is reversed from its previous state, the encoder should
         * invert the direction of the angle it returns. It does not only affect
         * subsequent changes to the encoder's angle, but previous angles as well.
         *
         * @param reversed whether the encoder should be reversed or not
         */
        virtual void setReversed(bool reversed) = 0;
        /**
         * @brief Get the gear ratio of the encoder
         *
         * @return float teeth of driven gear / teeth of driving gear
         */
        virtual float getGearRatio() = 0;
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
        virtual void setGearRatio(float gearRatio) = 0;
        /**
         * @brief Destroy the Encoder object
         *
         */
        virtual ~Encoder();
};
