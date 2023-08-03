#include "external_wifi_network.h"
#include "WiFi.h"
#include "unity.h"

char* test_ssid = "TheAttic";
char* test_password = "nosoupforyou";

/*****************************************************************/
/*  Testing of the ESP32 connection to an external WiFi network  */
/*****************************************************************/
void test_function_station_mode(void) {
    TEST_ASSERT_TRUE(WiFi.getMode() == WIFI_MODE_STA);
}
void test_function_ESP32_connect_to_other_network(void) {
    TEST_ASSERT_TRUE(WiFi.status() == WL_CONNECTED);
    TEST_ASSERT_TRUE(WiFi.SSID() == test_ssid);
}
void test_function_scan_for_networks() {
    TEST_ASSERT_GREATER_THAN(1, WiFi.scanNetworks());
}

/*  Unity Test for external_wifi_network  */
int runUnityTests_extern_wifi_network() {
    UNITY_BEGIN();

    RUN_TEST(test_function_station_mode);
    RUN_TEST(test_function_ESP32_connect_to_other_network);
    RUN_TEST(test_function_scan_for_networks);

    return UNITY_END();
}

/*  Tear down for external_wifi_network  */
void tearDown_external_wifi_network() {
    WiFi.disconnect();
}

/*  Testing set up for external_wifi_network  */
void setup_external_wifi_network() {
    // Connect to the external network
    External_WiFi_Network extern_wifi_network = External_WiFi_Network(test_ssid, test_password);

    Serial.println();
    Serial.println(WiFi.SSID().c_str());
    Serial.println(test_ssid);
    Serial.println(WiFi.SSID() == test_ssid);

    delay(100);
  
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);
}