
#include "esphome/core/log.h"
#include "ads7828.h"

namespace esphome::ads7828 {


uint32_t Ads7828::get_channel_value(uint8_t ch, bool int_ref, bool diff_mode) const {
  if (ch >= esphome::ads7830::NCHAN) {
    //in differential mode, channels 0-3 are the same as 4-7 inverted
    ESP_LOGW(TAG, "Invalid chan %i", int(ch));
    return this->get_max_value();
  }
  uint8_t command_byte = esphome::ads7830::ADC_ON_MASK; // ADC always ON
  if (!diff_mode) command_byte |= esphome::ads7830::SINGLE_END_MASK;
  if (int_ref) command_byte |= esphome::ads7830::INTERNAL_REFERENCE_MASK;
  uint8_t bytes[2];
  command_byte |= (diff_mode ? ch : this->channel_map_[ch]) << esphome::ads7830::CHANNEL_INDEX_SHIFT;
  auto error_code = this->write_read(&command_byte, 1, bytes, 2);
  if (error_code) {
    ESP_LOGW(TAG, "Invalid write_read() %i", error_code);
    return this->get_max_value();
  }
  return (uint32_t(bytes[0]) << 8) | uint32_t(bytes[0]);
}

uint32_t Ads7828::get_max_value() const {
  return 1023;
}

} // namespace esphome::ads7828