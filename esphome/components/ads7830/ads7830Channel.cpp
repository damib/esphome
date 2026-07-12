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

float Ads7830Channel::sample_value(){
  switch (this->value_mode_){
    case VOLTAGE :
      return this->sample();
    case PERCENT :
      return 100.0 * this->sample_raw() / this->adc_->get_max_value(); 
    default:
      return this->sample_raw();  
  }
}

const char *ValueModeStr(ValueMode mode) {
  switch(mode){
    case RAW: return "RAW";
    case VOLTAGE: return "VOLTAGE";
    default : return "PERCENT";
  }
}

} // namespace esphome::ads7830