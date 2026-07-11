#include "ads7830Channel.h"
#include "ads7830.h"


namespace esphome::ads7830 {

float Ads7830Channel::sample() {
  if (!this->adc_) return NAN; // Sanity check. 
  return this->adc_->get_channel_voltage(this->channel_index_, this->use_internal_reference_, this->differential_mode_);
}

uint32_t Ads7830Channel::sample_raw(){
  if (!this->adc_) return 0xff; // Sanity check. 
  return this->adc_->get_channel_value(this->channel_index_, this->use_internal_reference_, this->differential_mode_);
}

} // namespace esphome::ads7830