#include "mqtt.h"
#include "external_wifi_network.h"
#include "unity.h"

MQTT mqtt_broker;

/*****************************************************************/
/*  Testing of the MQTT broker  */
/*****************************************************************/
void test_function_connection() {
    TEST_ASSERT_TRUE(mqtt_broker.connected());
}
void test_function_subscription() {
    bool sub = mqtt_broker.subscribe("optimal_moisture_level");
    TEST_ASSERT_TRUE(sub);
}
void test_function_receive_message() {
    std::pair<std::string, std::string> mqtt_pair = mqtt_broker.read_until_response();
    TEST_ASSERT_TRUE(mqtt_pair.first == "optimal_moisture_level");
    TEST_ASSERT_TRUE(mqtt_pair.second != "");
}
void test_function_publish() {
    bool pub = mqtt_broker.publish("optimal_moisture_level", "46");
    TEST_ASSERT_TRUE(pub);
}

int runUnityTests_mqtt(void) {
    UNITY_BEGIN();

    RUN_TEST(test_function_connection);
    RUN_TEST(test_function_subscription);
    RUN_TEST(test_function_receive_message);
    RUN_TEST(test_function_publish);

    return UNITY_END();
}

/*  Tear down for wifi_network  */
void tearDown_mqtt() {
    mqtt_broker.unsubscribe("optimal_moisture_level");
    mqtt_broker.disconnect();
    WiFi.disconnect();
}

void setup_mqtt() {
    External_WiFi_Network extern_wifi_network = External_WiFi_Network(test_ssid, test_password);

    if(extern_wifi_network.connected()) {
        // Connect to the MQTT broker
        mqtt_broker.connect();
    }

    delay(100);
  
    // Wait ~2 seconds before the Unity test runner
    // establishes connection with a board Serial interface
    delay(2000);
}