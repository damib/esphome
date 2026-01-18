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


#define ntim 40

bool BekoClimate::on_receive(remote_base::RemoteReceiveData data) {
  auto &raw = data.get_raw_data();
  int size = raw.size();
  int inx = 0;
  char line[(ntim+1)*5];
  while(inx < size){
    for(int i = 0; i < ntim && inx < size; i++, inx++) {
      snprintf(line+i*5, (ntim+1)*5, " % 4d", data[inx]);
    }
    ESP_LOGI(TAG, "%s", line);
  }
  return false;
}

}  // namespace beko
}  // namespace esphome
