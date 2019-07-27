# Using UART pins as GPIO
Most devices have a header containing GPIO pins for flashing and UART debugging (`RX` & `TX`). With some caution, these can also be used as GPIO pins.
In general I wouldn't prefer to use these pins but in some cases this is the only way of extending devices with extra sensors.

Because these pins are also used for sending & receiving UART commands, the first thing you need to do is disable UART logging. This can be done by adding the following to your yaml file:
```yaml
logger:
  ...
  baud_rate: 0
```
After that, the `RX` & `TX` pins can be used both as in- or output GPIO pins.

## Notes of caution
Some notes of caution:
- **If you burn these GPIO pins, there's no way of flashing via UART anymore**
- Both `RX` & `TX` are pulled high at boot
- Boot fails when `TX` is pulled low
- Some output may be generated on `TX` at the early boot stages

## Rules of thumb
Because of the notes of caution, I keep the following rules of thumb:
- Only use `RX` for either in- or outputs
- When applying i2c, use `TX` as data line and `RX` as clock line; the data line will probably get some data at early boot stages but because the clock line is held high at boot, none of it will be clocked to the slaves.