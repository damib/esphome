#pragma once

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "../ads7830Channel.h"

namespace esphome::ads7830 {

class BinarySensor : public binary_sensor::BinarySensor, public Ads7830Channel {
public:
  void update() override;
  void dump_config() override;
  void set_threshold(uint8_t th) { this->threshold_ = th; }
  void set_inverted(bool inverted) { this->inverted_ = inverted; }

protected:
  uint8_t threshold_{0};
  bool inverted_{false};
};

} // namespace esphome::ads7830
