#pragma once

#include "esphome/components/climate_ir/climate_ir.h"

namespace esphome {
namespace beko {

// Values for Beko IR Controllers
const uint8_t BEKO_TEMP_MIN = 16;  // Celsius
const uint8_t BEKO_TEMP_MAX = 30;  // Celsius


const uint8_t BEKO_STATE_FRAME_SIZE = 19;

class BekoClimate : public climate_ir::ClimateIR {
 public:
  BekoClimate()
      : climate_ir::ClimateIR(BEKO_TEMP_MIN, BEKO_TEMP_MAX, 1.0f, true, true,
                              {climate::CLIMATE_FAN_QUIET, climate::CLIMATE_FAN_AUTO, climate::CLIMATE_FAN_LOW,
                               climate::CLIMATE_FAN_MEDIUM, climate::CLIMATE_FAN_HIGH},
                              {climate::CLIMATE_SWING_OFF, climate::CLIMATE_SWING_VERTICAL,
                               climate::CLIMATE_SWING_HORIZONTAL, climate::CLIMATE_SWING_BOTH}) {}

 protected:
  // Transmit via IR the state of this climate controller.
  void transmit_state() override;
  uint8_t operation_mode_() const;
  uint16_t fan_speed_() const;
  uint8_t temperature_() const;
  // Handle received IR Buffer
  bool on_receive(remote_base::RemoteReceiveData data) override;
  bool parse_state_frame_(const uint8_t frame[]);
};

}  // namespace beko
}  // namespace esphome
