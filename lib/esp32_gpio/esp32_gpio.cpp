#include "esp32_gpio.h"

ESP32_GPIO::ESP32_GPIO() {
    pin_setup(MOISTURE_PIN, In);
    pin_setup(PH_PIN, In);
    pin_setup(PUMP_PIN, Out);
}

void ESP32_GPIO::pin_setup(int pin_num, PinType type) {
    Serial.begin(115200);
    if (type == In) {
        pinMode(pin_num, INPUT);
    } 
    else if (type == Out) {
        pinMode(pin_num, OUTPUT);
    }
}

int ESP32_GPIO::pin_analog_read(int pin_num) {
    // read the analog / millivolts value for the inputted pin number:
    int analogValue = analogRead(pin_num);
    int analogVolts = analogReadMilliVolts(pin_num);
  
    // print out the values you read:
    Serial.printf("ADC analog value = %d\n", analogValue);
    Serial.printf("ADC millivolts value = %d\n", analogVolts);

    // Clear data from the serial monitor
    delay(100);

    return analogValue;
}

int ESP32_GPIO::read_data(int pin_num) {
    return digitalRead(pin_num);
}

void ESP32_GPIO::write_data(int pin_num, int data) {
    digitalWrite(pin_num, data);
}

double ESP32_GPIO::read_moisture_level() {
    double moisture_voltage = analogRead(MOISTURE_PIN);
    moisture_voltage = moisture_voltage * (3.3 / 4095);
    Serial.println("Moisture Sensor voltage: ");
    Serial.println(moisture_voltage);

    // Convert voltage to moisture level
    double soil_density = ((-0.22) * moisture_voltage) + 0.5674;
    return soil_density;
}

double ESP32_GPIO::read_pH_level() {
    double pH_level = analogRead(PH_PIN);

    // TODO -- convert voltage to pH level

}

void ESP32_GPIO::output_pump_control(std::string start_or_stop) {
    if (start_or_stop == "start") {
        digitalWrite(PUMP_PIN, HIGH);
    }
    else if (start_or_stop == "stop") {
        digitalWrite(PUMP_PIN, LOW);
    }
}