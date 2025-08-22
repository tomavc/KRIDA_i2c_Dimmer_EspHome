# ESPHome I2C Dimmer Component

This repository provides an external component for [ESPHome](https://esphome.io/) 
to control [KRIDA Electronics I2C-based dimmer modules](https://www.tindie.com/products/bugrovs2012/i2c-4ch-ac-led-dimmer-module/)
It supports brightness control via I2C communication, with error handling and logging. The component is designed for ETH01 ESP32 devices, but should be easy to change for other devices.


## Features
- **I2C Control**: Send brightness values (inverted scale: 0-100) to specific I2C addresses and channels.
- **Brightness Only Mode**: Supports `BRIGHTNESS` and `ON_OFF` modes.
- **Error Handling**: Logs I2C initialization and write failures.
- **Debug Logging**: Optional debug logs for brightness changes.
- **Easy Configuration**: Define multiple instances in YAML with address and channel.

## Requirements
- ESPHome version 2025.2.0 or later (due to external components requirement).
- I2C bus configured in your ESPHome YAML (e.g., `i2c:` block).
- Compatible hardware: [KRIDA I2C Dimmer modules](https://www.tindie.com/products/bugrovs2012/i2c-4ch-ac-led-dimmer-module/).

## Installation
1. Copy the example.yaml file 