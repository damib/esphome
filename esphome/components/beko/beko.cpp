#include "beko.h"
#include "esphome/components/remote_base/remote_base.h"

namespace esphome {
namespace beko {
static const char *const TAG = "beko.climate";

void BekoClimate::transmit_state() {
}

uint8_t BekoClimate::operation_mode_() const {
  return 0;
}

uint16_t BekoClimate::fan_speed_() const {
  return 0;
}

uint8_t BekoClimate::temperature_() const {
  return BEKO_TEMP_MIN;
}

bool BekoClimate::parse_state_frame_(const uint8_t frame[]) {
  return true;
}

bool BekoClimate::on_receive(remote_base::RemoteReceiveData data) {
  auto &raw = data.get_raw_data();
  int size = raw.size();
  int inx = 0;
  char line[150];
  while(size - inx > 20){
    snprintf(line, 150, "% 4d % 4d % 4d % 4d % 4d % 4d % 4d % 4d % 4d % 4d % 4d % 4d % 4d % 4d % 4d % 4d % 4d % 4d % 4d % 4d",
      raw[inx], raw[inx+1], raw[inx+2], raw[inx+3], raw[inx+4], raw[inx+5], raw[inx+6], raw[inx+7], raw[inx+8], raw[inx+9],
      raw[inx+10], raw[inx+11], raw[inx+12], raw[inx+13], raw[inx+14], raw[inx+15], raw[inx+16], raw[inx+17], raw[inx+18], raw[inx+19]);
      inx += 20;
    ESP_LOGI(TAG, "%s", line);
  }
  for(int i = 0; i < data.size()-inx; i++) {
    snprintf(line+i*5, 150-i*5, " % 4d", data[inx+i]);
  }
  ESP_LOGI(TAG, "%s", line);
  return false;
}

}  // namespace beko
}  // namespace esphome
