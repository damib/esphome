
#include "esphome/core/log.h"
#include "ads7830.h"

namespace esphome::ads7830 {

static const char *const TAG = "ads7830.i2c";

uint8_t Ads7830::read_channel(uint8_t ch) {
  if (ch >= NCHAN) {
    //in differential mode, channels 0-3 are the same as 4-7 inverted
    ESP_LOGW(TAG, "Invalid chan %i", int(ch));
    return 255;
  }
  uint8_t cmd = ((this->differential_mode_ << (NCHAN-1-ch)) & 0x80)
              | (this->chmap_[ch] << 4) 
              | (((this->use_internal_reference_ >> ch) << 3) & 0x08) 
              | (0x1 << 2);
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

void Ads7830::set_differential_mode(uint8_t chno, bool differential_mode) {
  if (differential_mode)
    this->differential_mode_ &= ~(1 << chno);
  else
    this->differential_mode_ |= (1 << chno);
}

bool Ads7830::get_differential_mode(uint8_t chno) const {
  return !bool((this->differential_mode_>> chno) & 1); 
}

void Ads7830::set_use_internal_reference(uint8_t chno, bool use_internal_reference) {
  if (use_internal_reference)
    this->use_internal_reference_ |= (1 << chno);
  else
    this->use_internal_reference_ &= ~(1 << chno);
}

bool Ads7830::get_use_internal_reference(uint8_t chno) const {
  return bool(this->use_internal_reference_ & (1<<chno));
}

float Ads7830::get_channel_voltage(uint8_t ch) const {
  if (this->use_internal_reference_ & (1<<ch))
    return this->channels_[ch] * INTERNAL_REFERENCE / 255.0f; 
  return this->channels_[ch] * this->reference_voltage_ / 255.0f; 
}

}