#include "test_wifi_network.h"
#include "test_external_wifi_network.h"
#include "test_mqtt.h"

/********************************************************/
/*      Tests for all libraries in the project          */
/*      -- To test a specific library, uncomment        */
/*         that project's tearDown(), runUnityTests(),  */
/*         and setup() functions.                       */
/********************************************************/

void tearDown() {
    //tearDown_wifi_network();
    tearDown_external_wifi_network();
    //tearDown_mqtt();
}

int runUnityTests() {
    //runUnityTests_wifi_network();
    runUnityTests_extern_wifi_network();
    //runUnityTests_mqtt();
}

void setup() {
    //setup_wifi_network();
    setup_external_wifi_network();
    //setup_mqtt();

    runUnityTests();
}

void loop() {}