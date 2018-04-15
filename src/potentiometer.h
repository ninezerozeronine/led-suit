// Convenience class to use a potentiometer with Arduino

#ifndef potentiometer_h
#define potentiometer_h

#include "Arduino.h"

class Potentiometer {
    public:
        Potentiometer(
            uint8_t pin,
            uint8_t update_period,
            void (*callback)(uint8_t)
        );
        void init();
        uint8_t get_value();
        uint8_t de_log_and_map(uint16_t input);
        void update();

    private:
        // The pin this potentiometer is reading from
        uint8_t _pin;

        // The remapped value of the potentiometer
        uint8_t _value;

        // How many millisecods to wait between updates
        uint8_t _update_period;

        // When the last update was
        unsigned long _last_update;

        // Callback for when the value changes
        void (*_callback)(uint8_t);
};

#endif