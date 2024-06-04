#pragma once

#include "hardware/encoder/encoder.hpp"
#include <memory>

class TrackingWheel {
    public:
        /**
         * @brief Construct a new Tracking Wheel object
         *
         * @param encoder unique pointer to the encoder
         * @param radius radius of the tracking wheel
         * @param offset offset of the tracking wheel
         */
        TrackingWheel(std::unique_ptr<Encoder> encoder, Length radius, Length offset);
        /**
         * @brief Get the distance traveled by the tracking wheel
         *
         * @return Length
         */
        Length getDistance();
        /**
         * @brief Get the offset of the tracking wheel
         *
         * @return Length
         */
        Length getOffset();
        /**
         * @brief Get the radius of the tracking wheel
         *
         * @return Length
         */
        Length getRadius();
        /**
         * @brief set the distance traveled by the tracking wheel to 0
         *
         */
        void reset();
    private:
        const std::unique_ptr<Encoder> encoder;
        const Length radius;
        const Length offset;
};