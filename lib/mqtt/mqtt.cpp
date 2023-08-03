#include "mqtt.h"

std::string sub_payload = "";
char* sub_topic = "";

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received messages:");
  Serial.println(topic);

  std::string mqtt_payload = "";
  for (int i = 0; i < length; i++) {
    Serial.print(char(payload[i]));
    mqtt_payload = mqtt_payload + char(payload[i]);
  }

  // Save data from server
  sub_topic = topic;
  sub_payload = mqtt_payload;

  Serial.println();
}

MQTT::MQTT() {
    client = PubSubClient(espClient);
    espClient.setCACert(root_ca);
    client.setServer(server, port);
    client.setCallback(callback);
}

void MQTT::reconnect() {
  while(!client.connected()) {
    Serial.print("\nConnecting to ");
    Serial.println(server);
    if(client.connect("esp32", username, password)) {
      Serial.print("\nConnected to ");
      Serial.println(server);
      subscribe("optimal_moisture_level");
      subscribe("pH_level");
    } else {
      Serial.println("Trying to connect again");
      delay(5000);
    }
  }
}

void MQTT::connect() {
    if(!client.connected()) {
      reconnect();
    }
    client.loop();
}

bool MQTT::publish(char* topic, char* message) {
  return client.publish(topic, message);
}

bool MQTT::subscribe(char* topic) {
  return client.subscribe(topic);
}

bool MQTT::connected() {
  return client.connected();
}

void MQTT::disconnect() {
  client.disconnect();
}

void MQTT::unsubscribe(char* topic) {
  client.unsubscribe(topic);
}

void MQTT::read() {
  client.loop();
}

std::pair<std::string, std::string> MQTT::read_until_response() {
  std::string pay = "";
  std::string top = "";

  while(true) {
    read();

    top = sub_topic;
    pay = sub_payload;

    if (!sub_payload.empty()) {
      break;
    }
  }
  return std::make_pair(top, pay);
}