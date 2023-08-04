#include "unity.h"
#include "esp32_gpio.h"
#include "WiFi.h"

ESP32_GPIO gpio;

/***************************************************/
/*  Testing of the ESP32 GPIO functionality  */
/***************************************************/
void test_function_initial_pin_setup() {
    
}
void test_function_pin_input() {
    int pin_input[10];
    for (int i = 0; i < 10; i++) {
        pin_input[i] = gpio.pin_analog_read(MOISTURE_PIN);
    }
    TEST_ASSERT_NOT_NULL(pin_input);
}

/*  Unit Test for esp32_gpio    */
int runUnityTests_esp32_gpio() {
    UNITY_BEGIN();

    RUN_TEST(test_function_pin_input);

    return UNITY_END();
}

/*  Tear down for esp32_gpio  */
void tearDown_esp32_gpio() {
    WiFi.disconnect();
}

/*  Testing set up for esp32_gpio  */
void setup_esp32_gpio() {
    gpio = ESP32_GPIO();

    delay(100);
  
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);
}