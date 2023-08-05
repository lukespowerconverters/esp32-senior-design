#ifndef ESP32_GPIO_H_
#define ESP32_GPIO_H_

#include <iostream>
#include <Arduino.h>

#define BUILTIN_LED 2
#define MOISTURE_PIN 36
#define PH_PIN 22
#define PUMP_PIN 19

class ESP32_GPIO {
    private:

    public:
        enum PinType {In, Out};
        enum Color {Red, Green, Blue, White, Black};

        ESP32_GPIO();

        void pin_setup(int pin_num, PinType type);
        int pin_analog_read(int pin_num);

        int read_data(int pin_num);
        void write_data(int pin_num, int data);

        double read_moisture_level();
        double read_pH_level();

        void output_pump_control(std::string start_or_stop);
};

#endif /* ESP32_GPIO_H_ */