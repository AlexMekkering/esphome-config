![ESPHome](logo-text.svg)

This page is the starting point for all installation and configuration documentation of all my devices which are configured with [ESPHome](https://esphome.io/) .

# Installation
## Arch Linux
### Installing pip
Since platformio 4 we can just use python, which can be installed with `pacman -Syu python`

### Setting up a virtual environment
We setup a virtual environment with `python -m venv venv`

### Installing esphomeyaml in a virtual environment
In a virtual environment (`. venv/bin/activate`) call `pip install esphome`.

# Knowledge base
* [Powering sensors](PoweringSensors.md)
