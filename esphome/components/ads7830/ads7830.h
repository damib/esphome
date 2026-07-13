#pragma once

#include "esphome/components/logger/logger.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/component.h"


namespace esphome::ads7830 {

const int NCHAN = 8;
const float INTERNAL_REFERENCE = 2.5;
const uint8_t SINGLE_END_MASK = 0x80;
const uint8_t CHANNEL_INDEX_SHIFT = 4;
const uint8_t INTERNAL_REFERENCE_MASK = 0x08;
const uint8_t ADC_ON_MASK = 0x04;

/**
 * @brief Class to interface with the ADS7830 ADC chip.
 * This is a multiplexed 8-channel 8-bit ADC with I2C interface. 
 * It can be used to read analog voltages from multiple sources.
 * This class does not implement the VoltageSampler interface directly because
 * VoltageSampler class doesn't handle multiple channels, it provides insted methods 
 * to read raw values and voltages from the channels.
 * https://www.ti.com/product/ADS7830
 */

class Ads7830 : public Component, public i2c::I2CDevice {
protected:
  // The channel map for the ADS7830. This array maps the channel index to the corresponding command bits for the ADC.
  // This is valid only for single-ended mode, in differential mode channels 0-3 are the same as 4-7 inverted.
  const uint8_t channel_map_[NCHAN]={0,4,1,5,2,6,3,7};
  float external_reference_voltage_{0.0f};

public:
  /**
  * Usually TAG is  static constant in *.cpp file, here it is defined 
  * as class static constant so that it can be reused in other classes.
  * (Developer guide forbids only the use of static variables) 
  */
  constexpr static const char *const TAG = "ads7830";
  
  void dump_config() override;
  // This is virtual so support for similar ADC can be direved from this
  virtual uint32_t get_channel_value(uint8_t ch, bool int_ref, bool diff_mode) const;
  float get_channel_voltage(uint8_t ch, bool int_ref, bool diff_mode) const;
  float get_channel_normalized(uint8_t ch, bool int_ref, bool diff_mode) const;
  virtual uint32_t get_max_value() const; 
  void set_external_reference_voltage(float reference_voltage) { this->external_reference_voltage_ = reference_voltage; }
}; 

} // namespace esphome::ads7830