# My ESPHome Configuration

![ESPHome](logo-text.svg)

This page is the starting point for all installation and configuration documentation of all my devices which are configured with [ESPHome](https://esphome.io/) .

## Current setup

### Common firmware features

The following features are implemented for every device

- [Wifi](https://esphome.io/components/wifi.html) with failover [Access Point Mode](https://esphome.io/components/wifi.html#access-point-mode) and [Captive Portal](https://esphome.io/components/captive_portal.html)
- [Over The Air](https://esphome.io/components/ota.html) firware updates
- [Native API](https://esphome.io/components/api.html)
- [Web Server](https://esphome.io/components/web_server.html) with basic authentication
- [Status Binary Sensor](https://esphome.io/components/binary_sensor/status.html)
- [Wifi Info Text Sensor](https://esphome.io/components/text_sensor/wifi_info.html) (IP, SSID & BSSID)
- [Version Text Sensor](https://esphome.io/components/text_sensor/version.html)
- [Uptime Sensor](https://esphome.io/components/sensor/uptime.html) rounded to the hour to reduce updates
- [Restart Switch](https://esphome.io/components/switch/restart.html)
- Update interval of 10 minutes for most sensors to reduce updates

### Device types & specific firmware features

| Device | Type | Physical button | [GPIO power] | [UART GPIO] | [Script] | [Custom Sensor] |
| -- | -- |:--:|:--:|:--:|:--:|:--:|
| [attic_1]     | [Sonoff 4CH R2]             | X |   |   |   |   |
| [bedroom_1]   | [Sonoff 4CH Pro]            | X |   | X |   |   |
| [bedroom_2]   | [Sonoff S20]                | X |   | X |   |   |
| [garage]      | [Wemos D1 mini Pro v1.0.0]  |   |   |   |   |   |
| [living_1]    | [Sonoff 4CH]                | X |   | X |   |   |
| [smartmeter]  | [Wemos D1 mini Pro v1.0.0]  |   | X |   |   | X |
| [ventilation] | [Sonoff Pow R2]             | X |   |   | X |   |
| [veranda_wcd] | [Shelly 1]                  | X |   |   |   |   |
| [xmas_1]      | [Sonoff Dual R1]            | X |   |   |   | X |

### Sensors

| Device | [Status LED] | [bme280] ([i2c])  | [dallas] | [CSE7766] | [dht22] | [RF receiver] |
| -- |:--:|:--:|:--:|:--:|:--:|:--:|
| [attic_1]     | X |   |   |   |   | X |
| [bedroom_1]   |   | X |   |   |   |   |
| [bedroom_2]   |   |   |   |   |   | X |
| [garage]      | X |   | X |   | X |   |
| [living_1]    | X | X |   |   |   |   |
| [smartmeter]  | X | X |   |   |   |   |
| [ventilation] | X |   |   | X |   | X |
| [veranda_wcd] |   |   |   |   |   |   |
| [xmas_1]      | X |   |   |   |   |   |

## Installation

### Arch Linux

#### Installing python

Since platformio 4 we can just use python, which can be installed with `pacman -Syu python`.

#### Activating a virtual environment with esphome

There's an install script. Execute it with `. install.sh`
> Once setup, the virtual environment can be activated with `. venv/bin/activate`

#### Configuring secrets

The yaml files refer to secrets which are configured in `secrets.yaml`. This file is not kept in the GIT repository so should be created after a clean clone.
For this, you can copy the [Travis Secrets] to `secrets.yaml` and fill in your secrets.

## Knowledge base

- [Powering sensors](PoweringSensors.md)
- [Using UART as GPIO](UARTasGPIO.md)
- [Receiving RF Codes](RFReceiver.md)

[Travis Secrets]: https://github.com/AlexMekkering/esphome-config/blob/master/.travis-secrets.yaml
[Common Travis Secrets]: https://github.com/AlexMekkering/esphome-config/blob/master/common/.travis-secrets.yaml
[attic_1]: https://github.com/AlexMekkering/esphome-config/blob/master/attic_1.yaml
[bedroom_1]: https://github.com/AlexMekkering/esphome-config/blob/master/bedroom_1.yaml
[bedroom_2]: https://github.com/AlexMekkering/esphome-config/blob/master/bedroom_2.yaml
[garage]: https://github.com/AlexMekkering/esphome-config/blob/master/garage.yaml
[living_1]: https://github.com/AlexMekkering/esphome-config/blob/master/living_1.yaml
[smartmeter]: https://github.com/AlexMekkering/esphome-config/blob/master/smartmeter.yaml
[ventilation]: https://github.com/AlexMekkering/esphome-config/blob/master/ventilation.yaml
[veranda_wcd]: https://github.com/AlexMekkering/esphome-config/blob/master/veranda_wcd.yaml
[xmas_1]: https://github.com/AlexMekkering/esphome-config/blob/master/christmas_1.yaml
[Sonoff S20]: https://www.itead.cc/smart-socket.html
[NodeMCU v2]: https://github.com/nodemcu/nodemcu-devkit-v1.0
[Wemos D1 mini Pro v1.0.0]: https://wiki.wemos.cc/products:retired:d1_mini_pro_v1.0.0
[Sonoff 4CH]: https://www.itead.cc/sonoff-4ch.html
[Sonoff 4CH R2]: https://www.itead.cc/sonoff-4ch.html
[Sonoff 4CH Pro]: https://www.itead.cc/sonoff-4ch-pro.html
[Sonoff Pow R2]: https://www.itead.cc/sonoff-pow-r2.html
[Sonoff Dual R1]: https://www.itead.cc/sonoff-dual.html
[Shelly 1]: https://shelly.cloud/shelly1-open-source/
[Script]: https://esphome.io/guides/automations.html#script-execute-action
[Custom Sensor]: https://esphome.io/components/sensor/custom.html
[GPIO power]: PoweringSensors.md
[UART GPIO]: UARTasGPIO.md
[Status LED]: https://esphome.io/components/status_led.html
[bme280]: https://esphome.io/components/sensor/bme280.html
[i2c]: https://esphome.io/components/i2c.html
[dallas]: https://esphome.io/components/sensor/dallas.html
[CSE7766]: https://esphome.io/components/sensor/cse7766.html
[dht22]: https://esphome.io/components/sensor/dht.html
[RF Receiver]: RFReceiver.md
