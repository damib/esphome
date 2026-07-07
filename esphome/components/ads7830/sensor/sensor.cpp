

#include "sensor.h"
#include "../ads7830.h"

namespace esphome::ads7830 {

  void Sensor::update_value() {
    auto value = this->get_value();
    if (this->state != value)
      this->publish_state(value);
  };

}
