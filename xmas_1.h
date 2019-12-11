#include "esphome.h"

class SilF330Button : public Component, public UARTDevice, public BinarySensor {
    private:
        bool previously = false;

    public:
        SilF330Button(UARTComponent *parent) : UARTDevice(parent) {}

        void setup() override {
            // nothing to do here
        }

        void loop() override {
            const uint8_t expected1 = 0xA0;
            const uint8_t expected2[] = {0x00, 0x04};
            const uint8_t expected3[] = {0x01, 0x04, 0x05};
            const uint8_t expected4 = 0xA1;

            bool trigger = false;
            for (int i = 1; i <= 4; i++) {
                bool ok = available();
                if (ok) {
                    char c = read();
                    switch(i) {
                        case 1:
                            ok = c == expected1;
                            break;
                        case 2:
                            ok = false;
                            for (int j = 1; !ok && j <= sizeof(expected2); j++) {
                                ok = c == expected2[j - 1];
                            }
                            break;
                        case 3:
                            ok = false;
                            for (int j = 1; !ok && j <= sizeof(expected3); j++) {
                                ok = c == expected3[j - 1];
                            }
                            break;
                        case 4:
                            ok = c == expected4;
                            trigger = ok;
                            break;
                    }
                    if (ok) {
                        ESP_LOGD("Button", "UART byte %d (0x%x) was as expected", i, c);
                    } else {
                        ESP_LOGD("Button", "Unsupported UART byte %d (0x%x) received", i, c);
                    }
                } else {
                    break;
                }
            }
            if (trigger != previously) {
                ESP_LOGD("Button", "Button state change detected");
                publish_state(trigger);
                previously = trigger;
            }
        }

};