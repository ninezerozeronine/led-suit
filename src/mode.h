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
        virtual void initialise_pot_0(unsigned long current_millis) {}
        virtual void initialise_pot_1(unsigned long current_millis) {}
        virtual void initialise_pot_2(unsigned long current_millis) {}
        virtual void initialise_pot_3(unsigned long current_millis) {}
        virtual void initialise_pot_4(unsigned long current_millis) {}
        virtual void initialise_button_0(unsigned long current_millis) {}

        virtual void process_new_pot_0_value(uint16_t value) {}
        virtual void process_new_pot_1_value(uint16_t value) {}
        virtual void process_new_pot_2_value(uint16_t value) {}
        virtual void process_new_pot_3_value(uint16_t value) {}
        virtual void process_new_pot_4_value(uint16_t value) {}
        virtual void button_0_pressed() {}
        virtual void button_0_released() {}
    protected:
        void constructor_defaults();
        CRGB * leds;
};

#endif