# Receiving RF Codes using [rc-switch]

Receiving RF codes using cheap RF receivers (I use cheap Superheterodyne receivers like QIACHIP RX470-4, RX500-4 or WL101-341) can be done using the [Remote Receiver] component.

The following [Remote Receiver] configuration works for all my RF remotes:

```yaml
remote_receiver:
  pin: <PIN>
  dump:
    - rc_switch
  tolerance: 60%
  filter: 4us
  idle: 4ms
```

After this, decoded RF codes can be monitored when the logging level is set to `DEBUG`.

## Binary Sensors

When you recorded the RF code of one of your keyfobs, you can turn that into a `binary_sensor` as follows:

```yaml
binary_sensor:
  ...
  - platform: remote_receiver
    name: RF Button Keyfob1
    rc_switch_raw:
      protocol: 1
      code: !secret rf_code_keyfob1
    filters:
      - delayed_off: 100ms
  ...
```

> The secret `rf_code_keyfob1` needs to be added to `secrets.yaml`

You can even add some automation to your binary sensor by adding e.g.:

```yaml
    on_press:
      then:
        - switch.toggle: switch_1
```

> When the `binary_sensor` triggers an automation you can choose not to report it to Home Assistant by removing the `name` attributed and add an `id` attribute (or add `internal: true`).

[rc-switch]: https://github.com/sui77/rc-switch
[Remote Receiver]: https://esphome.io/components/remote_receiver.html
