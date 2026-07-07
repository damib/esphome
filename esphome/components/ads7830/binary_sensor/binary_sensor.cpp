

#include "binary_sensor.h"

namespace esphome::ads7830 {

static const char *const TAG = "binary_sensor.ad7830.i2c";

void BinarySensor::update_value() {
  auto value = this->get_value();
  this->publish_state(this->inverted_ ? value < this->th_ : value >= this->th_);
};

}