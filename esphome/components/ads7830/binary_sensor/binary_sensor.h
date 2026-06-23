#pragma once

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "../ads7830Channel.h"

namespace esphome::ads7830 {

class BinarySensor : public binary_sensor::BinarySensor, public Ads7830Channel {
public:
  void update() override;
  void set_threshold(uint8_t th) { this->th_ = th; }

protected:
  uint8_t th_;
};

} // namespace empty_component
