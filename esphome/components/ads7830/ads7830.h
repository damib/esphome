#pragma once

#include "esphome/components/logger/logger.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/component.h"


namespace esphome::ads7830 {

const int NCHAN = 8;
const float INTERNAL_REFERENCE = 2.5;

class Ads7830 : public i2c::I2CDevice, public PollingComponent {
private:
  const uint8_t chmap_[NCHAN]={0,4,1,5,2,6,3,7};
  float reference_voltage_{2.5f};
  uint8_t  use_internal_reference_{8};
  uint8_t  differential_mode_{255};
  uint8_t channels_[NCHAN];

protected:
  uint8_t read_channel(uint8_t ch);

public:
  Ads7830() {}
  uint8_t get_channel_value(uint8_t ch) const { return this->channels_[ch]; }
  void set_external_reference_voltage(float reference_voltage) { this->reference_voltage_ = reference_voltage; }
  float get_external_reference_voltage() const { return this->reference_voltage_; }
  float get_channel_voltage(uint8_t ch) const;
  void set_use_internal_reference(uint8_t chno, bool use_internal_reference);
  bool get_use_internal_reference(uint8_t chno) const;
  void set_differential_mode(uint8_t chno, bool differential_mode);
  bool get_differential_mode(uint8_t chno) const;
  void update() override;
}; 

} // namespace esphome::ads7830