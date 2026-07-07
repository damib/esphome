
#include "esphome/core/log.h"
#include "ads7830.h"

namespace esphome::ads7830 {


uint8_t Ads7830::get_channel_value(uint8_t ch, bool int_ref, bool diff_mode) const {
  if (ch >= NCHAN) {
    //in differential mode, channels 0-3 are the same as 4-7 inverted
    ESP_LOGW(TAG, "Invalid chan %i", int(ch));
    return 255;
  }
  uint8_t cmd = 0x04; // ADC always ON
  cmd |= (diff_mode ? ch : this->channel_map_[ch])  << 4;
  if (!diff_mode)
    cmd |= 0x80;
  if (int_ref)
    cmd |= 0x01 << 3;
  auto error_code = this->write_read(&cmd, 1, nullptr, 0);
  if (error_code) {
    ESP_LOGW(TAG, "Invalid write %i", error_code);
    return 255;
  }
  uint8_t rval;
  error_code = this->read(&rval, 1);
  if (error_code) {
    ESP_LOGW(TAG, "Invalid read %i", error_code);
    return 255;
  }
  return rval;
}

float Ads7830::get_channel_voltage(uint8_t ch, bool int_ref, bool diff_mode) const {
  auto val = this->get_channel_value(ch, int_ref, diff_mode);
  return val / 255.0f * (int_ref ? INTERNAL_REFERENCE : this->external_reference_voltage_); 
}

void Ads7830::dump_config() {
  ESP_LOGCONFIG(TAG, "ADS7830:");
  ESP_LOGCONFIG(TAG, "  Ext. ref. : %.3fV", double(this->external_reference_voltage_));
}

} // namespace esphome::ads7830