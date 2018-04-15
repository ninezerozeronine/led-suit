// Convenience class to use a button with Arduino
// 
// To use a button, have it ground the pin it's connected to when pressed.

#include "button.h"

// Constructor
//
// pin - the pin the button is connected to
// debounce_time - the number of miliseconds for the button to be in it's new state before considering it pressed
// low_to_high_callback - the callback to call when the button goes from unpressed to pressed
// high_to_low_callback - the callback to call when the button goes from pressed to unpressed
Button::Button(uint8_t pin, uint8_t debounce_time, void (*low_to_high_callback)()=NULL, void (*high_to_low_callback)()=NULL) {
    _pin = pin;
    _debounce_time = debounce_time;
    _is_pressed = false;
    _last_state = HIGH;
    _last_state_change = 0;
    _low_to_high_callback = low_to_high_callback;
    _high_to_low_callback = high_to_low_callback;
}

// Set up button ready for use.
// Note that we're using INPUT_PULLUP to save on having to add a resistor
void Button::init() {
    pinMode(_pin, INPUT_PULLUP);
    _is_pressed, _last_state = !digitalRead(_pin);
}

// Update the button each time round the main loop
void Button::update() {
    // Read state of the button (invert because we're using INPUTPULLUP)
    int current_state = !digitalRead(_pin);

    // If the button is in a different state to the current pressed state
    if (current_state != _is_pressed) {

        // Get current time
        unsigned long current_time = millis();

        // If the button is in the same state as it was last time
        if (current_state == _last_state) {

            // If it's been in this new state for longer that the debounce time, flip the state
            // and call the callbacks
            if (current_time - _last_state_change > _debounce_time) {
                _is_pressed = current_state;
                if (current_state == HIGH) {
                    if (_low_to_high_callback != NULL) {
                        _low_to_high_callback();
                    }
                } else {
                    if (_high_to_low_callback != NULL) {
                        _high_to_low_callback();
                    }
                }
            }

        // Else the button has just changed state
        } else {
            // Set the last state and record the time
            _last_state = current_state;
            _last_state_change = current_time;
        }
    }
}
