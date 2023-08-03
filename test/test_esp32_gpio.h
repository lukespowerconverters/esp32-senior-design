#include "unity.h"
#include "esp32_gpio.h"

ESP32_GPIO gpio;

/***************************************************/
/*  Testing of the ESP32 GPIO functionality  */
/***************************************************/
void test_function_initial_pin_setup() {
    
}


/*  Unit Test for esp32_gpio    */
int runUnityTests_esp32_gpio() {
    UNITY_BEGIN();



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