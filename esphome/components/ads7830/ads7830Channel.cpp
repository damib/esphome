#include "ads7830Channel.h"
#include "ads7830.h"


namespace esphome::ads7830 {

float Ads7830Channel::sample() { 
  return this->adc_->get_channel_voltage(this->ch_);
};

uint8_t Ads7830Channel::get_value(){
  return this->adc_->get_channel_value(this->ch_);
}

} // namespace esphome::ads7830