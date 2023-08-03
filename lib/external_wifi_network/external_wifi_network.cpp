#include "external_wifi_network.h"

External_WiFi_Network::External_WiFi_Network() {
}

External_WiFi_Network::External_WiFi_Network(char* SSID_in, char* password_in) {
    connect_To_WiFi(SSID_in, password_in);
}

void External_WiFi_Network::setup_external_wifi_network() {
    Serial.begin(115200);

    // Set WiFi to station mode, disconnect from previous AP
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");

    // Call function to scan for available local networks
    scan_for_networks();
}

int External_WiFi_Network::scan_for_networks(void) {
    Serial.println("Scan start");

    // WiFi.scanNetworks will return the number of networks found.
    int n = WiFi.scanNetworks();
    Serial.println("Scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.printf("%2d",i + 1);
            Serial.print(" | ");
            Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
            Serial.print(" | ");
            Serial.printf("%4d", WiFi.RSSI(i));
            Serial.print(" | ");
            Serial.printf("%2d", WiFi.channel(i));
            Serial.print(" | ");
            switch (WiFi.encryptionType(i))
            {
            case WIFI_AUTH_OPEN:
                Serial.print("open");
                break;
            case WIFI_AUTH_WEP:
                Serial.print("WEP");
                break;
            case WIFI_AUTH_WPA_PSK:
                Serial.print("WPA");
                break;
            case WIFI_AUTH_WPA2_PSK:
                Serial.print("WPA2");
                break;
            case WIFI_AUTH_WPA_WPA2_PSK:
                Serial.print("WPA+WPA2");
                break;
            case WIFI_AUTH_WPA2_ENTERPRISE:
                Serial.print("WPA2-EAP");
                break;
            case WIFI_AUTH_WPA3_PSK:
                Serial.print("WPA3");
                break;
            case WIFI_AUTH_WPA2_WPA3_PSK:
                Serial.print("WPA2+WPA3");
                break;
            case WIFI_AUTH_WAPI_PSK:
                Serial.print("WAPI");
                break;
            default:
                Serial.print("unknown");
            }
            Serial.println();
            delay(10);
        }
    }
    Serial.println("");

    // Delete the scan result to free memory for code below.
    WiFi.scanDelete();

    // Wait a bit before scanning again.
    delay(5000);

    // Return the number of networks detected
    return n;
}

void External_WiFi_Network::set_SSID(char* SSID_in) {
    SSID = SSID_in;
}

char* External_WiFi_Network::get_SSID(void) {
    return SSID;
}

void External_WiFi_Network::set_password(char* password_in) {
    password = password_in;
}

char* External_WiFi_Network::get_password(void) {
    return password;
}

bool External_WiFi_Network::connected() {
    return WiFi.isConnected();
}

void External_WiFi_Network::connect_To_WiFi(char* SSID_in, char* password_in) {
    Serial.begin(115200);

    // Switch from AP to station mode
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    WiFi.begin(SSID_in, password_in);
    Serial.println("connecting");

    while (!WiFi.isConnected()) {
        Serial.print(".");
        delay(100);
    }

    Serial.println();
    Serial.print("Connected to WiFi Network: ");
    String current_ssid = WiFi.SSID();
    Serial.println(current_ssid);

    set_SSID(SSID_in);
    set_password(password_in);
}

void External_WiFi_Network::disconnect() {
    WiFi.disconnect();
}