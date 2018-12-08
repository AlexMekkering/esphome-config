// Auto generated code by esphomeyaml
#include "esphomelib/application.h"

#include "esphomelib/log.h"
#include "esphomelib/esphal.h"
#include "esphomelib/espmath.h"

static const char *TAG = "sensor.power_consumption";
static const char *NAME = "Power Consumption";
static const uint8_t PIN = 12;
static const uint32_t MIN_MSEC_BETWEEN_PULSES = 150; // 150ms (or 24kW)
static const uint32_t MAX_MSEC_BETWEEN_PULSES = 36000000; // 10h (or 0.1Wh)
static const float PULSES_PER_KWH = 1000.0f;
static const float FACTOR = 3600000.0f / PULSES_PER_KWH;
static const uint32_t UPDATE_INTERVAL = 10000; // 10s interval

using namespace esphomelib;
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

class CustomSensor : public sensor::PollingSensorComponent {
  private:
    GPIOInputPin *pin;

  public:
    CustomSensor(uint8_t pin, uint32_t update_interval) : sensor::PollingSensorComponent(NAME, update_interval) {
        this->pin = new GPIOInputPin(pin);
    }

    void setup() override {
      ESP_LOGCONFIG(TAG, "Setting up %s on pin %d ...", NAME, this->pin->get_pin());
      this->pin->setup();

      attachInterrupt(this->pin->get_pin(), gpio_intr, RISING);

      this->clear_filters();
    }

    void update() override {
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
          ESP_LOGD(TAG, "%s: Virtual pulse of %d msecs generated", NAME, interval);
          ESP_LOGD(TAG, "%s: Last known real pulse took %d msecs", NAME, previous_interval);
        } else {
          ESP_LOGD(TAG, "%s: Real pulse which took %d msecs, was seen %d msecs ago", NAME, interval, delta);
          ESP_LOGD(TAG, "%s: Last pulse bounced %d times for %d msecs in total", NAME, nr_of_bounces, bounce_msecs);
        }
        float value = FACTOR / float(interval);
        this->push_new_value(value);
      } else {
        if (last_pulse == 0) {
          ESP_LOGD(TAG, "%s: Waiting for first pulse to be detected...", NAME);
        } else {
          ESP_LOGD(TAG, "%s: Waiting for second pulse to be detected...", NAME);
        }
      }
    }

    std::string unit_of_measurement() override { return "kW"; }

    int8_t accuracy_decimals() override { return 3; }

    std::string icon() override { return "mdi:power-plug"; }
};

void setup() {
  // ===== DO NOT EDIT ANYTHING BELOW THIS LINE =====
  // ========== AUTO GENERATED CODE BEGIN ===========
  App.set_name("smartmeter");
  App.set_compilation_datetime(__DATE__ ", " __TIME__);
  ::LogComponent *_logcomponent = App.init_log(115200);
  _logcomponent->set_global_log_level(ESPHOMELIB_LOG_LEVEL_INFO);
  ::WiFiComponent *_wificomponent = App.init_wifi();
  _wificomponent->set_sta(::WiFiAp{
      .ssid = " ",
      .password = "",
      .channel = -1,
  });
  ::OTAComponent *_otacomponent = App.init_ota();
  _otacomponent->start_safe_mode();
  mqtt::MQTTClientComponent *mqtt_mqttclientcomponent = App.init_mqtt("127.0.0.1", 1883, "", "");
  ::Application::MakeWiFiSignalSensor _application_makewifisignalsensor = App.make_wifi_signal_sensor("WiFi Signal");
  sensor::WiFiSignalSensor *sensor_wifisignalsensor = _application_makewifisignalsensor.wifi;
  sensor::MQTTSensorComponent *sensor_mqttsensorcomponent = _application_makewifisignalsensor.mqtt;
  ::Application::MakeUptimeSensor _application_makeuptimesensor = App.make_uptime_sensor("Uptime Sensor");
  sensor::UptimeSensor *sensor_uptimesensor = _application_makeuptimesensor.uptime;
  sensor::MQTTSensorComponent *sensor_mqttsensorcomponent_2 = _application_makeuptimesensor.mqtt;
  ::StatusLEDComponent *_statusledcomponent = App.make_status_led(::GPIOOutputPin(2, OUTPUT, true));
  ::Application::MakeDHTSensor _application_makedhtsensor = App.make_dht_sensor("Meterkast Temperatuur", "Meterkast Luchtvochtigheid", 14);
  sensor::DHTComponent *sensor_dhtcomponent = _application_makedhtsensor.dht;
  _application_makedhtsensor.dht->set_dht_model(sensor::DHT_MODEL_DHT22);
  sensor::DHTTemperatureSensor *sensor_dhttemperaturesensor = _application_makedhtsensor.dht->get_temperature_sensor();
  sensor::MQTTSensorComponent *sensor_mqttsensorcomponent_3 = _application_makedhtsensor.mqtt_temperature;
  sensor::DHTHumiditySensor *sensor_dhthumiditysensor = _application_makedhtsensor.dht->get_humidity_sensor();
  sensor::MQTTSensorComponent *sensor_mqttsensorcomponent_4 = _application_makedhtsensor.mqtt_humidity;
  // =========== AUTO GENERATED CODE END ============
  // ========= YOU CAN EDIT AFTER THIS LINE =========

  auto *custom_sensor = new CustomSensor(PIN, UPDATE_INTERVAL);
  App.register_component(custom_sensor);
  App.register_sensor(custom_sensor);

  App.setup();
}

void loop() {
  App.loop();
  delay(16);
}
