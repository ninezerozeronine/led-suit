/*
Mode ideas

* Light on press
* Light up 1-n LEDs controlling hue, saturation and value
* Light worms that move on a grid and have a trail
* Light streaks that move in one direction
* Pulse that eminates from the centre outwards (hard/soft, speed, hue, sat)
* Stripes that move horizontally or vertically (hard/soft, speed, hue, sat)
* looping horizontal/vertical rainbow (speed)
* Pulsing solid colour (hard/soft, speed, hue, sat)
* Perlin noise colour (speed)
* Write a message



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
        virtual void initialise_pot_0(int value) {}
        virtual void initialise_pot_1(int value) {}
        virtual void initialise_pot_2(int value) {}
        virtual void initialise_pot_3(int value) {}
        virtual void initialise_pot_4(int value) {}
        virtual void initialise_button_0(byte state) {}

        virtual void process_new_pot_0_value(int value) {}
        virtual void process_new_pot_1_value(int value) {}
        virtual void process_new_pot_2_value(int value) {}
        virtual void process_new_pot_3_value(int value) {}
        virtual void process_new_pot_4_value(int value) {}
        virtual void button_0_pressed() {}
        virtual void button_0_released() {}
    protected:
        void constructor_defaults();
        CRGB * leds;
};

#endif