#include "esphome.h"

using namespace esphome;

static const char *TAG = "sensor.power_consumption";
static const uint32_t MIN_MSEC_BETWEEN_PULSES = 200; // 200ms (or 18kW max.)
static const uint32_t MAX_MSEC_BETWEEN_PULSES = 36000000; // 10h (or 0.1Wh min.)

volatile uint32_t last_pulse = 0;
volatile uint32_t next_to_last_pulse = 0;
volatile uint32_t last_bounce = 0;
volatile uint32_t nr_of_bounces = 0;
volatile uint32_t bounce_msecs = 0;
volatile uint32_t nr_of_pulses = 0;

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
      nr_of_pulses++;
    } else {
      nr_of_bounces++;
      bounce_msecs += bounce;
    }
  } else {
    // initialize first pulse seen since boot
    next_to_last_pulse = now;
    last_bounce = now;
    last_pulse = now;
    nr_of_pulses = 1;
  }
}

class SmartMeterSensor : public PollingComponent {
  private:
    GPIOInputPin *pin;
    float factor;

  public:
    sensor::Sensor *power_consumption_sensor = new sensor::Sensor();
    sensor::Sensor *total_consumption_sensor = new sensor::Sensor();

    SmartMeterSensor(uint8_t pin, uint32_t update_interval = 10000, float pulses_per_kwh = 1000.0f) : PollingComponent(update_interval) {
        this->pin = new GPIOInputPin(pin);
        this->factor = 3600000.0f / pulses_per_kwh;
    }

    void setup() override {
      ESP_LOGCONFIG(TAG, "Setting up %s on pin %d ...", power_consumption_sensor->get_name().c_str(), pin->get_pin());
      pin->setup();

      attachInterrupt(pin->get_pin(), gpio_intr, RISING);

      power_consumption_sensor->clear_filters();
      total_consumption_sensor->clear_filters();
    }

    void update() override {
      const char * name = power_consumption_sensor->get_name().c_str();
      switch(nr_of_pulses) {
        case 0:
          ESP_LOGD(TAG, "%s: Waiting for first pulse to be detected...", name);
          total_consumption_sensor->publish_state(0.0);
          break;
        case 1:
          ESP_LOGD(TAG, "%s: Waiting for second pulse to be detected...", name);
          total_consumption_sensor->publish_state(0.001);
          break;
        default:
          uint32_t delta = millis() - last_pulse;
          uint32_t interval = last_pulse - next_to_last_pulse;
          if (delta > interval) {
            ESP_LOGD(TAG, "%s: Virtual pulse of %d msecs generated", name, delta);
            ESP_LOGD(TAG, "%s: Last known real pulse took %d msecs", name, interval);
          } else {
            ESP_LOGD(TAG, "%s: Real pulse which took %d msecs, was seen %d msecs ago", name, interval, delta);
            ESP_LOGD(TAG, "%s: Last pulse bounced %d times for %d msecs in total", name, nr_of_bounces, bounce_msecs);
            total_consumption_sensor->publish_state(float(nr_of_pulses) / 1000.0);
          }
          power_consumption_sensor->publish_state(factor / float(interval));
          break;
      }
    }
};
