#pragma once

#include "esphome/components/logger/logger.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/core/component.h"
#include "esphome/components/ads7830/ads7830.h"

namespace esphome::ads7828 {

/**
 * @brief Class to interface with the 12 bit version of the ads7830 named ads7828
 * Reuses most of the code of the ads7830.
 */

class Ads7828 : public esphome::ads7830::Ads7830 {
public:
  
  // This is virtual so support for similar ADC can be direved from this
  virtual uint32_t get_channel_value(uint8_t ch, bool int_ref, bool diff_mode) const;
  virtual uint32_t get_max_value() const; 
}; 

} // namespace esphome::ads7828