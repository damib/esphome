

#include "sensor.h"
#include "../ads7830.h"

namespace esphome::ads7830 {

  static const char *const TAG = "sensor.ads7830.i2c";

  void Sensor::setup() {};
  void Sensor::dump_config() {};
  void Sensor::update() {
    uint8_t st = this->get_value();
    if (this->state != st)
      this->publish_state(st);
  };

}
