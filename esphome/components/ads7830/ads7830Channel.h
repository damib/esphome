
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/voltage_sampler/voltage_sampler.h"

namespace esphome::ads7830 {

class Ads7830;

class Ads7830Channel : public PollingComponent, public voltage_sampler::VoltageSampler {
public:
  float get_setup_priority() const override { return setup_priority::HARDWARE; }
  void set_adc_instance(Ads7830 *p, uint8_t ch) { this->adc_ = p; this->ch_ = ch; }
  void set_use_internal_reference(bool ir);
  void set_differential_mode(bool dm);
  float sample() override;
  uint8_t get_value();

protected:
  Ads7830 *adc_;
  uint8_t ch_;
};

} // namespace esphome::ads7830