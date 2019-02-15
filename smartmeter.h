#include "esphomelib.h"

using namespace esphomelib;

static const char *TAG = "sensor.power_consumption";
static const uint32_t MIN_MSEC_BETWEEN_PULSES = 150; // 150ms (or 24kW)
static const uint32_t MAX_MSEC_BETWEEN_PULSES = 36000000; // 10h (or 0.1Wh)

volatile uint32_t last_pulse = 0;
volatile uint32_t next_to_last_pulse = 0;
volatile uint32_t last_bounce = 0;
volatile uint32_t nr_of_bounces = 0;
volatile uint32_t bounce_msecs = 0;

/**
 * As this is an interrupt routine, don't add logging here
**/
void ICACHE_RAM_ATTR gpio_intr() {
  uint32_t now = millis();
  if (last_pulse != 0) {
    uint32_t bounce = now - last_bounce;
    last_bounce = now;
    if (bounce > MIN_MSEC_BETWEEN_PULSES) {
      nr_of_bounces = 0;
      bounce_msecs = 0;
      next_to_last_pulse = last_pulse;
      last_pulse = now;
    } else {
      nr_of_bounces++;
      bounce_msecs += bounce;
    }
  } else {
    // initialize first pulse seen since boot
    next_to_last_pulse = now;
    last_bounce = now;
    last_pulse = now;
  }
}

class SmartMeterSensor : public PollingComponent, public sensor::Sensor {
  private:
    GPIOInputPin *pin;
    float factor;

  public:
    SmartMeterSensor(char *name, uint8_t pin, uint32_t update_interval = 10000, float pulses_per_kwh = 1000.0f) : PollingComponent(update_interval) {
        this->pin = new GPIOInputPin(pin);
        this->factor = 3600000.0f / pulses_per_kwh;
        this->set_name(name);
    }

    void setup() override {
      ESP_LOGCONFIG(TAG, "Setting up %s on pin %d ...", get_name().c_str(), pin->get_pin());
      pin->setup();

      attachInterrupt(pin->get_pin(), gpio_intr, RISING);

      clear_filters();
    }

    void update() override {
      const char * name = get_name().c_str();
      uint32_t local_last_pulse = last_pulse;
      uint32_t local_next_to_last_pulse = next_to_last_pulse;
      uint32_t msec_between_pulses = local_last_pulse - local_next_to_last_pulse;
      if (msec_between_pulses != 0) {
        uint32_t now = millis();
        uint32_t interval = msec_between_pulses;
        uint32_t delta = now - local_last_pulse;
        if (delta > interval) {
          uint32_t previous_interval = interval;
          interval = delta;
          ESP_LOGD(TAG, "%s: Virtual pulse of %d msecs generated", name, interval);
          ESP_LOGD(TAG, "%s: Last known real pulse took %d msecs", name, previous_interval);
        } else {
          ESP_LOGD(TAG, "%s: Real pulse which took %d msecs, was seen %d msecs ago", name, interval, delta);
          ESP_LOGD(TAG, "%s: Last pulse bounced %d times for %d msecs in total", name, nr_of_bounces, bounce_msecs);
        }
        publish_state(factor / float(interval));
      } else {
        if (last_pulse == 0) {
          ESP_LOGD(TAG, "%s: Waiting for first pulse to be detected...", name);
        } else {
          ESP_LOGD(TAG, "%s: Waiting for second pulse to be detected...", name);
        }
      }
    }

    std::string unit_of_measurement() override { return "kW"; }

    int8_t accuracy_decimals() override { return 3; }

    std::string icon() override { return "mdi:power-plug"; }

};
