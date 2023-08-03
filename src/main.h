#ifndef MAIN_H_
#define MAIN_H_

#include "external_wifi_network.h"
#include "mqtt.h"
#include "esp32_gpio.h"
#include <string>

extern External_WiFi_Network external_wifi_network;
extern ESP32_GPIO gpio;
extern MQTT mqtt_broker;

extern char* moisture_topic;
extern char* pH_topic;
extern char* comeplete_topic;

extern bool done_listening;

extern double pH_Level;
extern double Moisture_Level;
extern double pH_Data;
extern double Moisture_Data;

void set_values(std::string topic, std::string message) {
    if (topic == pH_topic) {
        pH_Level = ::atof(message.c_str());
    } 
    else if (topic == moisture_topic) {
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
    mqtt_broker.subscribe(pH_topic);
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

#endif /* MAIN_H */