#include "external_wifi_network.h"
#include "mqtt.h"
#include "esp32_gpio.h"
#include "database.h"
#include "main.h"
#include <string>

void setup()
{
    input_settings();

}

void loop() {
    read_sensors();

    delay(10000);

    motor_on_off();
}
