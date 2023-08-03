#ifndef WIFI_NETWORK_H_
#define WIFI_NETWORK_H_

#include "WebServer.h"
#include "WiFi.h"
//#include "ESPAsyncWebServer.h"
#include <Wire.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

class WiFi_Network {
    private:
        char* ssid;
        char* password;
        IPAddress local_ip;
        IPAddress gateway;
        IPAddress subnet;

    public:
        WiFi_Network();
        WiFi_Network(char* SSID_in, char* password_in);
        
        void set_SSID(char* SSID_in);
        char* get_SSID(void);
        void set_password(char* password_in);
        char* get_password(void);
        void set_local_ip(IPAddress local_ip_in);
        IPAddress get_local_ip(void);
        void set_gateway(IPAddress gateway_in);
        IPAddress get_gateway(void);
        void set_subnet(IPAddress subnet_in);
        IPAddress get_subnet(void);

        void first_setup();
        void start_AP_config();
        void connect();
        void wait_for_device_connection();

        void disconnect();
};

#endif /* WIFI_NETWORK_H_ */