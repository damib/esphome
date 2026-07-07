
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/voltage_sampler/voltage_sampler.h"

namespace esphome::ads7830 {

class Ads7830;

/**
 * @brief Class to interface with a single channel of the ADS7830 ADC chip.
 * This class provides methods to read raw values and voltages from a specific channel of the ADS7830.
 * It also allows configuring the channel's differential mode and internal reference usage.
 * Sensors are derived from this class to provide specific functionality for different types of sensors.
 * It implements the VoltageSampler interface to provide a standard way to sample voltage readings from the channel.
 */

class Ads7830Channel : public PollingComponent, public voltage_sampler::VoltageSampler {
public:
  void set_adc_instance(Ads7830 *p, uint8_t ch);
  void set_use_internal_reference(bool ir);
  void set_differential_mode(bool dm);
  float sample() override;
  virtual void update_value() = 0;
  uint8_t get_value();

protected:
  Ads7830 *adc_;
  uint8_t ch_;
};

} // namespace esphome::ads7830