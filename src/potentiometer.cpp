// Convenience class to use a potentiometer with Arduino
// 
// To use pots, connect the outer pins of the pot to ground and +5v, then the 
// middle pin to the analog input pin chosen.

#include "potentiometer.h"

// Constructor
// 
// pin - The pin the potentiometer is reading from
// update_period - How long to wait in milliseconds before re-reading the potentiometer value
// callback - the function to call when the value of the potentiometer changes
Potentiometer::Potentiometer(
    uint8_t pin,
    uint8_t update_period,
    void (*callback)(uint8_t))
    {
    _pin = pin;
    _update_period = update_period;
    _callback = callback;
    _last_update = 0;
}

// Initialise the object
//
// Don't do this in the constructor so we're in control
void Potentiometer::init() {
    pinMode(_pin, INPUT);
    _value = de_log_and_map(analogRead(_pin));
    _last_update = millis();

}

// Get the current value of the potentiometer
uint8_t Potentiometer::get_value() {
    return _value;
}

// Need to do this de-logging because I bought logarithmic rather than 
// linear potentiometers :(
uint8_t Potentiometer::de_log_and_map(uint16_t input) {
    uint8_t result = 0;
    if (input <= 150) {
        result = map(input, 0, 150, 0, 128);
    } else {
        result = map(input, 151, 1023, 129, 255);
    }
    return result;
}

// Update the potentiometer
//
// To be called once every time the main loop runs
void Potentiometer::update() {
    // Get current time
    unsigned long current_time = millis();

    // If it's time to re-read the pot
    if (current_time - _last_update > _update_period) {
        // Store this read time
        _last_update = current_time;

        // Get the current value
        uint8_t test_val = de_log_and_map(analogRead(_pin));

        // Need to do this because the output is really noisy :(
        signed char diff = test_val - _value;
        if (abs(diff) > 2) {
            // Store it
            _value = test_val;

            // Call the callback
            if (_callback != NULL) {
                _callback(_value);
            }
        }
    }
}