#include "ads7830Channel.h"
#include "ads7830.h"


namespace esphome::ads7830 {

void Ads7830Channel::set_adc_instance(Ads7830 *p, uint8_t ch) {
  this->adc_ = p;
  this->ch_ = ch;
  this->adc_->register_channel(this);
}

float Ads7830Channel::sample() { 
  return this->adc_->get_channel_voltage(this->ch_);
};

void Ads7830Channel::set_differential_mode(bool dm) {
  this->adc_->set_differential_mode(this->ch_, dm);
}

void Ads7830Channel::set_use_internal_reference(bool ir) {
  this->adc_->set_use_internal_reference(this->ch_, ir);
}

uint8_t Ads7830Channel::get_value() {
  return this->adc_->get_channel_value(this->ch_);
}

} // namespace esphome::ads7830