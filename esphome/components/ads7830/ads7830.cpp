
#include "esphome/core/log.h"
#include "ads7830.h"

namespace esphome::ads7830 {

static const char *const TAG = "ads7830.i2c";

uint8_t Ads7830::read_channel(uint8_t ch) {
  if (ch > 7) {
    //in differential mode, channels 0-3 are the same as 4-7
    ESP_LOGW(TAG, "Invalid chan %i", int(ch));
    return 255;
  }
  uint8_t cmd = this->differential_mode_ | this->chmap_[ch] << 4 | this->use_internal_reference_ | 0x1 << 2;
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
  if(this->channels_[ch] != rval)
    ESP_LOGVV(TAG, "Ch%i new value %02x)", ch, rval);
  return rval;
}

void Ads7830::update(){
  for (int i = 0; i < 8; i++) {
    this->channels_[i] = read_channel(i);
  }
}

}