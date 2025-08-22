#include "esphome/core/component.h"
#include "esphome/components/light/light_output.h"
#include "esphome/components/light/light_traits.h"
#include "esphome/components/light/light_state.h"
#include <Wire.h>

namespace esphome {
namespace i2c_dimmer {

class I2CDimmerOutput : public Component, public light::LightOutput {
 public:
  void set_i2c_address(uint8_t i2c_address) { this->i2c_address_ = i2c_address; }
  void set_channel(uint8_t channel) { this->channel_ = channel; }

  void setup() override {
    Wire.beginTransmission(this->i2c_address_);
    if (Wire.endTransmission() != 0) {
      ESP_LOGW("I2CDimmer", "Failed to initialize I2C device at address 0x%02X", this->i2c_address_);
    }
  }

  light::LightTraits get_traits() override {
    auto traits = light::LightTraits();
    traits.set_supported_color_modes({light::ColorMode::BRIGHTNESS, light::ColorMode::ON_OFF});
    return traits;
  }

  void write_state(light::LightState *state) override {
    uint8_t brightness = 100;
    if (state->current_values.get_state()) {
      brightness = (uint8_t)(100 - (int)(state->current_values.get_brightness() * 100));
    }
    ESP_LOGD("I2CDimmer", "Writing brightness %d to address 0x%02X, channel 0x%02X", brightness, this->i2c_address_, this->channel_);
    Wire.beginTransmission(this->i2c_address_);
    Wire.write(this->channel_);
    Wire.write(brightness);
    if (Wire.endTransmission() != 0) {
      ESP_LOGE("I2CDimmer", "Failed to write to I2C device at address 0x%02X, channel 0x%02X", this->i2c_address_, this->channel_);
    }
    delayMicroseconds(500);  // Experimental: Small delay to space I2C commands during rapid transitions (adjust or remove if issues)
  }

 protected:
  uint8_t i2c_address_;
  uint8_t channel_;
};

}  // namespace i2c_dimmer
}  // namespace esphome