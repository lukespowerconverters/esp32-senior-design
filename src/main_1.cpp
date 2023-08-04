#include "external_wifi_network.h"
#include "mqtt.h"
#include "esp32_gpio.h"
#include "database.h"
#include "main.h"
#include <string>

void setup()
{
    
}

void loop() {
    gpio.pin_analog_read(MOISTURE_PIN);

    delay(5000);
}
