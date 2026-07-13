#include "ads7830Channel.h"
#include "ads7830.h"


namespace esphome::ads7830 {

float Ads7830Channel::sample() {
  if (!this->adc_) return NAN; // Sanity check. 
  return this->adc_->get_channel_voltage(this->channel_index_, this->use_internal_reference_, this->differential_mode_);
}

float Ads7830Channel::sample_value(){
  if (!this->adc_) return NAN; // Sanity check.
  switch (this->value_mode_){
    case VOLTAGE :
      return this->sample();
    case PERCENT :
      return this->adc_->get_channel_normalized(this->channel_index_, this->use_internal_reference_, this->differential_mode_); 
    default: // RAW
      return this->adc_->get_channel_value(this->channel_index_, this->use_internal_reference_, this->differential_mode_); 
  }
}

const char *ValueModeStr(ValueMode mode) {
  switch(mode){
    case RAW : return "RAW";
    case VOLTAGE : return "VOLTAGE";
    default : return "PERCENT";
  }
}

} // namespace esphome::ads7830