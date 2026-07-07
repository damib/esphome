#pragma once

#include "esphome/components/sensor/sensor.h"
#include "../ads7830Channel.h"

namespace esphome::ads7830 {

class Sensor : public sensor::Sensor, public Ads7830Channel {
public:
  void dump_config() override;
  void update() override;

};

} // namespace esphome