/*
Mode instances:

Initial
-------
* Must have an update method that is passed the current time
* Have functions that will be called when buttons are pressed or potentiometers adjusted.
* Are expected to set the LED array in the update method (but not show it)
* Must be dynamically creatable and deletable

Stretch
-------
* Must have a name
* Must give descriptions of what each button and pot do (for the screen!)
*/

#ifndef MODE_H
#define MODE_H

#include <Arduino.h>
#include <FastLED.h>

class Mode {
    public:
        Mode();
        Mode(CRGB* leds_);
        virtual void update(unsigned long current_millis) = 0;
        virtual void initialise(unsigned long current_millis) = 0;
        void pot_0(int value) {}
        void pot_1(int value) {}
        void pot_2(int value) {}
        void pot_3(int value) {}
        void pot_4(int value) {}
        void button_0_pressed() {}
        void button_0_released() {}
    protected:
        void constructor_defaults();
        CRGB * leds;
};

#endif