# Powering Sensors

You can simply power sensors by using an available `3v3` and `GND` pin but if there's no such pin available you can create extra ones by sacrifycing GPIO pins.

## Creating extra `GND` pins

Creating extra `GND` pins can be done by adding the following to your configuration file:

```yaml
output:
  - platform: gpio
    pin: <PIN>
    id: <SENSOR-NAME>_gnd
```

## Creating extra `3v3` pins

Creating extra `3v3` pins can be done by adding the following to your configuration file:

```yaml
output:
  - platform: gpio
    pin: <PIN>
    id: <SENSOR-NAME>_supply
```

... and add the following to put in `ON`:

```yaml
esphomeyaml:
  ...
  on_boot:
  - priority: 90
    then:
    - output.turn_on: <SENSOR-NAME>_supply
```
