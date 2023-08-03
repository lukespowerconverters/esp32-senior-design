#ifndef EXTERNAL_WIFI_NETWORK_H_
#define EXTERNAL_WIFI_NETWORK_H_

#include "WiFi.h"

class External_WiFi_Network {
    private:
        char* SSID;
        char* password;

    public:
        External_WiFi_Network();
        External_WiFi_Network(char* SSID_in, char* password);

        int scan_for_networks();
        void setup_external_wifi_network();
        void connect_To_WiFi(char* SSID_in, char* password);

        void set_SSID(char* SSID_in);
        char* get_SSID(void);
        void set_password(char* password_in);
        char* get_password(void);

        bool connected();
        void disconnect();
};

#endif /* EXTERNAL_WIFI_NETWORK_H_ */
