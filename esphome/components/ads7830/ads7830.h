#pragma once

#include "esphome/components/logger/logger.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/component.h"


namespace esphome::ads7830 {

const int NCHAN = 8;

class Ads7830 : public i2c::I2CDevice, public PollingComponent {
private:
  const uint8_t chmap_[NCHAN]={0,4,1,5,2,6,3,7};
  float reference_voltage_{2.5f};
  uint8_t  use_internal_reference_{8};
  uint8_t  differential_mode_{128};
  uint8_t channels_[NCHAN];

protected:
  uint8_t read_channel(uint8_t ch);

public:
  Ads7830() {}
  uint8_t get_channel_value(uint8_t ch) const { return this->channels_[ch]; }
  void set_reference_voltage(float reference_voltage) { this->reference_voltage_ = reference_voltage; }
  float get_reference_voltage() const { return this->reference_voltage_; }
  float get_channel_voltage(uint8_t ch) const { return this->channels_[ch] * this->reference_voltage_ / 255.0f; }
  void set_internal_reference(bool use_internal_reference) { this->use_internal_reference_ = use_internal_reference ? 8 : 0; }
  bool get_internal_reference() const { return bool(this->use_internal_reference_); }
  void set_differential_mode(bool differential_mode) { this->differential_mode_ = differential_mode ? 0 : 128; }
  bool get_differential_mode() const { return !bool(this->differential_mode_); }
  void update() override;
}; 

} // namespace esphome::ads7830