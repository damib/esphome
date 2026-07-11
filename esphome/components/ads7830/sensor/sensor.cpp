

#include "sensor.h"
#include "../ads7830.h"

namespace esphome::ads7830 {

void Sensor::dump_config() {
  ESP_LOGCONFIG(Ads7830::TAG, "Sensor:");
  ESP_LOGCONFIG(Ads7830::TAG, "  Chan : %u", this->channel_index_);
  ESP_LOGCONFIG(Ads7830::TAG, "  Int ref : %s", YESNO(this->use_internal_reference_));
  ESP_LOGCONFIG(Ads7830::TAG, "  Diff mode : %s", YESNO(this->differential_mode_));
}

void Sensor::update() {
  this->publish_state(this->sample_raw());
}

}
