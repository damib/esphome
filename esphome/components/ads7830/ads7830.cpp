
#include "esphome/core/log.h"
#include "ads7830.h"

namespace esphome::ads7830 {


uint32_t Ads7830::get_channel_value(uint8_t ch, bool int_ref, bool diff_mode) const {
  if (ch >= NCHAN) {
    //in differential mode, channels 0-3 are the same as 4-7 inverted
    ESP_LOGW(TAG, "Invalid chan %i", int(ch));
    return this->get_max_value();
  }
  uint8_t command_byte = ADC_ON_MASK; // ADC always ON
  if (!diff_mode) command_byte |= SINGLE_END_MASK;
  if (int_ref) command_byte |= INTERNAL_REFERENCE_MASK;
  command_byte |= (diff_mode ? ch : this->channel_map_[ch]) << CHANNEL_INDEX_SHIFT;
  uint8_t rval;
  auto error_code = this->write_read(&command_byte, 1, &rval, 1);
  if (error_code) {
    ESP_LOGW(TAG, "Invalid write_read() %i", error_code);
    return this->get_max_value();
  }
  return uint32_t(rval);
}

float Ads7830::get_channel_voltage(uint8_t ch, bool int_ref, bool diff_mode) const {
  auto val = this->get_channel_value(ch, int_ref, diff_mode);
  return val / this->get_max_value() * (int_ref ? INTERNAL_REFERENCE : this->external_reference_voltage_); 
}

float Ads7830::get_channel_normalized(uint8_t ch, bool int_ref, bool diff_mode) const {
  auto val = this->get_channel_value(ch, int_ref, diff_mode);
  return 100.0 * val / this->get_max_value();
}

void Ads7830::dump_config() {
  ESP_LOGCONFIG(TAG, "ADS7830:");
  ESP_LOGCONFIG(TAG, "  Ext. ref. : %.3fV", double(this->external_reference_voltage_));
}

uint32_t Ads7830::get_max_value() const {
  return 255;
}

} // namespace esphome::ads7830