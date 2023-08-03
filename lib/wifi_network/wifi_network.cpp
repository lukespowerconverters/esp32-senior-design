#include "wifi_network.h"

WiFi_Network::WiFi_Network() {
    ssid = "ESP32";
    password = "#SeniorDesign2023";
    
    /*set_local_ip((192,168,1,1));
    set_gateway((192,168,1,1));
    set_subnet((255,255,255,0));*/
}

WiFi_Network::WiFi_Network(char* SSID_in, char* password_in) {
    set_SSID(SSID_in);
    set_password(password_in);   
            
    start_AP_config();
}

void WiFi_Network::set_SSID(char* SSID_in) {
    ssid = SSID_in;
}

void WiFi_Network::set_password(char* password_in) {
    password = password_in;
}

char* WiFi_Network::get_SSID(void) {
    return ssid;
}

char* WiFi_Network::get_password(void) {
    return password;
}

void WiFi_Network::set_local_ip(IPAddress local_ip_in) {
    local_ip = local_ip_in;
}

IPAddress WiFi_Network::get_local_ip(void) {
    return local_ip;
}

void WiFi_Network::set_gateway(IPAddress gateway_in) {
    gateway = gateway_in;
}

IPAddress WiFi_Network::get_gateway(void) {
    return gateway;
}

void WiFi_Network::set_subnet(IPAddress subnet_in) {
    subnet = subnet_in;
}

IPAddress WiFi_Network::get_subnet(void) {
    return subnet;
}

void WiFi_Network::connect() {
    // Switch to Access Point/Station mode
    WiFi.mode(WIFI_AP_STA);

    // Connect to access point with original IP address
    if (!WiFi.config(local_ip, gateway, subnet)) {
        log_e("AP Connection failed.");
    }

    Serial.print("AP IP address: ");
    Serial.print(local_ip);
}

void WiFi_Network::start_AP_config(void) {
    Serial.begin(115200);
    Serial.println();
    WiFi.mode(WIFI_AP);
    Serial.println("Configuring access point...");

    // Set up ESP32 as access point
    if (!WiFi.softAP(ssid, password)) {
        log_e("Soft AP creation failed.");
        while(1);
    }

    // Get IP address of access point
    local_ip = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(local_ip);
}

void WiFi_Network::wait_for_device_connection() {
    Serial.println();
    Serial.print("Wait for device connection");
    while (WiFi.softAPgetStationNum() < 1) {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("Connected");
}

void WiFi_Network::disconnect() {
    WiFi.softAPdisconnect();
}