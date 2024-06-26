#include "hardware/trackingWheel.hpp"

TrackingWheel::TrackingWheel(std::shared_ptr<Encoder> encoder, Length radius, Length offset)
    : encoder(encoder),
      radius(radius),
      offset(offset) {}

Length TrackingWheel::getDistance() { return to_sDeg(encoder->getPosition()) * radius; }

Length TrackingWheel::getOffset() { return offset; }

Length TrackingWheel::getRadius() { return radius; }

void TrackingWheel::reset() { encoder->tare(); }