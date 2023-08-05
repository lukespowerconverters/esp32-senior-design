#include "external_wifi_network.h"
#include "mqtt.h"
#include "esp32_gpio.h"
#include "database.h"
#include "WiFi.h"
#include "main.h"
#include <string>

External_WiFi_Network network;
ESP32_GPIO gpio;
MQTT mqtt_broker;

char* moisture_topic;
char* comeplete_topic;
bool done_listening;
double Moisture_Level;
double Moisture_Data;

void set_values(std::string topic, std::string message) {
    if (topic == moisture_topic) {
        Moisture_Level = ::atof(message.c_str());
    }
    else if ((topic == comeplete_topic) && (message == "DONE")) {
        done_listening = true;
    }
}

void input_settings() {
    // Read user inputted settings from Node-Red
    mqtt_broker.connect();
    mqtt_broker.subscribe(moisture_topic);
    mqtt_broker.subscribe(comeplete_topic);

    while(!done_listening) {
        mqtt_broker.read();

        std::string s(sub_topic);
        set_values(s, sub_payload);
    }

    Serial.println("Initial settings complete:");
}

void read_sensors() {
    // Read sensors for allotted time
    Moisture_Data = gpio.read_moisture_level();
    //pH_Data = gpio.read_pH_level();

    char moisture_out = char(Moisture_Data);
    //char pH_out = char(pH_Data);

    mqtt_broker.publish("moisture_data", &moisture_out);
    //mqtt_broker.publish("pH_data", &pH_out);
}

void motor_on_off() {
    Serial.println();

    gpio.output_pump_control("start");
    Serial.println("ON");
    delay(5000);
    gpio.output_pump_control("stop");
    Serial.println("OFF");
}

void setup()
{
    network = External_WiFi_Network("TheAttic", "nosoupforyou");
    gpio = ESP32_GPIO();

    input_settings();
}

void loop() {
    read_sensors();

    delay(10000);

    motor_on_off();
}
