#pragma once

#include "esphome/core/component.h"
#include "esphome/core/log.h"
#include "esphome/components/i2c/i2c.h"
#include "esphome/components/light/light_output.h"
#include "esphome/components/light/light_traits.h"
#include "esphome/components/light/light_state.h"

namespace esphome {
namespace i2c_dimmer {

static const char *const TAG = "I2CDimmer";

class I2CDimmerOutput : public Component, public light::LightOutput, public i2c::I2CDevice {
 public:
  void set_channel(uint8_t channel) { this->channel_ = channel; }

  void setup() override {
    // Zero-length write acts as a probe, same as Wire.beginTransmission/endTransmission did
    if (this->write(nullptr, 0) != i2c::ERROR_OK) {
      ESP_LOGW(TAG, "Failed to initialize I2C device at address 0x%02X", this->address_);
    }
  }

  light::LightTraits get_traits() override {
    auto traits = light::LightTraits();
    traits.set_supported_color_modes({light::ColorMode::BRIGHTNESS});
    return traits;
  }

  void write_state(light::LightState *state) override {
    uint8_t brightness = 0;
    if (state->current_values.get_state()) {
      brightness = (uint8_t) (state->current_values.get_brightness() * 100);
    }
    ESP_LOGD(TAG, "Writing brightness %d to address 0x%02X, channel 0x%02X", brightness, this->address_,
             this->channel_);
    uint8_t data[2] = {this->channel_, brightness};
    if (this->write(data, sizeof(data)) != i2c::ERROR_OK) {
      ESP_LOGE(TAG, "Failed to write to I2C device at address 0x%02X, channel 0x%02X", this->address_,
               this->channel_);
    }
  }

 protected:
  uint8_t channel_;
};

}  // namespace i2c_dimmer
}  // namespace esphome
