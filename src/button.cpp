/*
  Push button functionality
*/

#include "Button.h"

// Constructor
Button::Button(uint8_t pin, uint8_t debounce_time, void (*callback)()) {
    _pin = pin;
    _debounce_time = debounce_time;
    _is_pressed = false;
    _last_read = HIGH;
    _last_activation = 0;
    _callback = callback;
}

// Set up button ready for use.
// Note that we're using INPUT_PULLUP to save on havnig to add a resistor
void Button::init() {
    pinMode(_pin, INPUT_PULLUP);
}

// Update the button each time round the main loop
void Button::update() {
    // Read state of the button
    int current_read = digitalRead(_pin);

    // If the button is on
    if (current_read == LOW) {

        // If the button isn't already activated
        if (_is_pressed == false) {
      
            // Get current time
            unsigned long current_time = millis();
  
            // If it was on before
            if (_last_read == LOW) {
      
                // If it's been on for longer that the debounce time set state to on, otherwise just keep waiting
                if (current_time - _last_activation > _debounce_time) {
                    // The button is on - set the state to on and call the callback
                    _is_pressed = true;
                    if (_callback != NULL) {
                        _callback();
                    }
                }
            // Else it's just turned on, track when it turned on, and that it's on    
            } else {
                _last_activation = current_time;
                _last_read = LOW;
            }
        }
    // Else the button is off. reset counters and set state to off
    } else {
        _is_pressed = false;
        _last_read = HIGH;
    }
}
