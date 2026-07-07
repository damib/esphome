

#include "binary_sensor.h"
#include "../ads7830.h"

namespace esphome::ads7830 {

void BinarySensor::dump_config() {
  ESP_LOGCONFIG(Ads7830::TAG, "Binary Sensor:");
  ESP_LOGCONFIG(Ads7830::TAG, "  Chan : %u", this->channel_index_);
  ESP_LOGCONFIG(Ads7830::TAG, "  Int ref : %s", YESNO(this->use_internal_reference_));
  ESP_LOGCONFIG(Ads7830::TAG, "  Diff mode : %s", YESNO(this->differential_mode_));
  ESP_LOGCONFIG(Ads7830::TAG, "  Thrs : %u", this->threshold_);
  ESP_LOGCONFIG(Ads7830::TAG, "  Inverted : %s", YESNO(this->inverted_));
}

void BinarySensor::update() {
  uint8_t aval = this->get_value();
  this->publish_state(this->inverted_ ? aval < this->threshold_ : aval >= this->threshold_);
}

}