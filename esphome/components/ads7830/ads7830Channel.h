
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/voltage_sampler/voltage_sampler.h"

namespace esphome::ads7830 {

class Ads7830; // Forward declaration

/**
 * @brief Class to interface with a single channel of the ADS7830 ADC chip.
 * This class provides methods to read raw values and voltages from a specific channel of the ADS7830.
 * It also allows configuring the channel's differential mode and internal reference usage.
 * Sensors are derived from this class to provide specific functionality for different types of sensors.
 * It implements the VoltageSampler interface to provide a standard way to sample voltage readings from the channel.
 */

class Ads7830Channel : public PollingComponent, public voltage_sampler::VoltageSampler {
public:
  void set_adc_instance(Ads7830 *p, uint8_t ch) { this->adc_ = p; this->channel_index_ = ch; }
  void set_use_internal_reference(bool ir) { this->use_internal_reference_ = ir; }
  void set_differential_mode(bool dm) { this->differential_mode_ = dm; }
  void set_use_raw_value(bool rv) { this->use_raw_value_ = rv; }
  float sample() override; // Always return a voltage
  float sample_value() { return this->use_raw_value_ ? this->sample_raw() : this->sample(); }

protected:
  uint32_t sample_raw();

  Ads7830 *adc_;
  uint8_t channel_index_;
  bool use_internal_reference_{false};
  bool differential_mode_{false};
  bool use_raw_value_{false};
};

} // namespace esphome::ads7830