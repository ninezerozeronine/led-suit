/*
    Push button functionality
*/

#ifndef button_h
#define button_h

#include "Arduino.h"

class Button
{
    public:
        Button(uint8_t pin, uint8_t debounce_time, void (*callback)());
        void init();
        void update();

    private:
        // The pin this button is connected to
        uint8_t _pin;
  
        // The time in milliseconds for the state to be held before considering it to be on
        uint8_t _debounce_time;

        // Whether the button is pressed or not
        bool _is_pressed;
    
        // The state of the pin read at the last update
        bool _last_read;
    
        // When the button last transitioned from low to high (without bouncing)
        unsigned long _last_activation;

        // Callback for when the button is pressed
        void (*_callback)();
};

#endif