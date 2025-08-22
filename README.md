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
1. setup your yaml file, making sure to set up your i2c correctly
2. add this:

```

external_components:
  - source: github://tomavc/KRIDA_i2c_Dimmer_EspHome@main
    components: [i2c_dimmer]

packages:
  my_modules:
    url: https://github.com/tomavc/KRIDA_i2c_Dimmer_EspHome
    path: components/i2c_dimmer/yaml
    refresh: 1s  # Optional: Refresh interval
    files:
      - path: module_4ch.yaml  # Module 1
        vars:
          address: 0x27
          ch1_name: "Kitchen"
          ch2_name: "WC"
          ch3_name: "Living Room"
          ch4_name: "Conservatory"
          transition_length: 2s
      - path: module_3ch.yaml  # Module 2
        vars:
          address: 0x26
          ch1_name: "Hallway Lights"
          ch2_name: "Staircase Lights"
          ch3_name: "External Lights"
          transition_length: 2s
```
3. If you are only using 1 or 2 or 3 channels on your i2c, then use module_1ch.yaml, module_2ch.yaml, or module_3ch.yaml.
4. view example.yaml for a full working yaml.

