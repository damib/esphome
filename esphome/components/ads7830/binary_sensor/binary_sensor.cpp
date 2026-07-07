

#include "binary_sensor.h"

namespace esphome::ads7830 {

static const char *const TAG = "binary_sensor.ad7830.i2c";

void BinarySensor::update() {
  uint8_t aval = this->get_value();
  this->publish_state(this->inverted_ ? aval < this->th_ : aval >= this->th_);
};

}