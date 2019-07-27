![ESPHome](logo-text.svg)

This page is the starting point for all installation and configuration documentation of all my devices which are configured with [ESPHome](https://esphome.io/) .

# Current setup

## Device types & firmware features

| device | type | physical button | [GPIO power] | [UART GPIO] | [script] | custom sensor |
| -- | -- |:--:|:--:|:--:|:--:|:--:|
| [attic_1]     | [Sonoff 4CH R2]             | X |   |   |   |   |
| [bedroom_1]   | [Sonoff 4CH Pro]            | X |   | X |   |   |
| [bedroom_2]   | [Sonoff S20]                | X |   | X |   |   |
| [garage]      | [Wemos D1 mini Pro v1.0.0]  |   |   |   |   |   |
| [living_1]    | [Sonoff 4CH]                | X |   | X |   |   |
| [smartmeter]  | [Wemos D1 mini Pro v1.0.0]  |   | X |   |   | X |
| [ventilation] | [Sonoff Pow]                | X |   | X | X |   |
| [veranda_wcd] | [Shelly 1]                  |   |   |   |   |   |

## Sensors

| device | bme280 | dallas | hlw8012 | dht22 | [RF receiver] |
| -- |:--:|:--:|:--:|:--:|:--:|
| [attic_1]     | X |   |   |   | X |
| [bedroom_1]   | X |   |   |   |   |
| [bedroom_2]   |   |   |   |   | X |
| [garage]      |   | X |   | X |   |
| [living_1]    | X |   |   |   |   |
| [smartmeter]  | X |   |   |   |   |
| [ventilation] |   |   | X |   | X |
| [veranda_wcd] |   |   |   |   |   |

# Installation
## Arch Linux
### Installing python
Since platformio 4 we can just use python, which can be installed with `pacman -Syu python`.

### Activating a virtual environment with esphome
There's an install script. Execute it with `. install.sh`
> Once setup, the virtual environment can be activated with `. venv/bin/activate`

### Configuring secrets
The yaml files refer to secrets which are configured in `secrets.yaml` and `common/secrets.yaml`. These files are not kept in the GIT repository so should be created for a clean clone or checkout.
For this, you can copy the [Travis Secrets] and [Common Travis Secrets] to the respective `secrets.yaml` files and fill in your secrets.

# Knowledge base
* [Powering sensors](PoweringSensors.md)

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
[Sonoff S20]: https://www.itead.cc/smart-socket.html
[NodeMCU v2]: https://github.com/nodemcu/nodemcu-devkit-v1.0
[Wemos D1 mini Pro v1.0.0]: https://wiki.wemos.cc/products:retired:d1_mini_pro_v1.0.0
[Sonoff 4CH]: https://www.itead.cc/sonoff-4ch.html
[Sonoff 4CH R2]: https://www.itead.cc/sonoff-4ch.html
[Sonoff 4CH Pro]: https://www.itead.cc/sonoff-4ch-pro.html
[Sonoff Pow]: https://www.itead.cc/sonoff-pow.html
[Shelly 1]: https://shelly.cloud/shelly1-open-source/
[script]: https://esphome.io/guides/automations.html#script-execute-action
[GPIO power]: PoweringSensors.md
[UART GPIO]: UARTasGPIO.md
[RF Receiver]: RFReceiver.md
