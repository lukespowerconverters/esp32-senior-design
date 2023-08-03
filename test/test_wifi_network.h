#include "unity.h"
#include "WiFi.h"
#include "wifi_network.h"

/***************************************************/
/*  Testing of the ESP32 WiFi network  */
/***************************************************/
void test_function_access_point_mode() {
    TEST_ASSERT_TRUE(WiFi.getMode() == WIFI_MODE_AP);
}
void test_function_ESP32_connected_to_ESP32_network() {
    TEST_ASSERT_TRUE_MESSAGE(WiFi.softAPSSID() == "ESP32", WiFi.softAPSSID().c_str());
}
void test_function_device_connected_to_ESP32_network() {
    TEST_ASSERT_TRUE(WiFi.softAPgetStationNum() == 1);
}

/*  Unity Test for wifi_network  */
int runUnityTests_wifi_network() {
    UNITY_BEGIN();

    RUN_TEST(test_function_access_point_mode);
    RUN_TEST(test_function_ESP32_connected_to_ESP32_network);
    RUN_TEST(test_function_device_connected_to_ESP32_network);

    return UNITY_END();
}

/*  Tear down for wifi_network  */
void tearDown_wifi_network() {
    WiFi.disconnect();
}

/*  Testing set up for wifi_network  */
void setup_wifi_network() {
    char* test_esp_ssid = "ESP32";
    char* test_esp_password = "#SeniorDesign2023";

    WiFi_Network wifi_network = WiFi_Network(test_esp_ssid, test_esp_password);
    wifi_network.wait_for_device_connection();

    delay(100);
  
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);
}