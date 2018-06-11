#ifndef RAINBOW_LOOP_H
#define RAINBOW_LOOP_H

#include <Arduino.h>
#include "mode.h"
#include "constants.h"

class RainbowLoop: public Mode {
    public:
        RainbowLoop();
        RainbowLoop(CRGB* leds_);
        virtual void update(unsigned long current_millis);
        virtual void initialise_pot_0(int value);
        virtual void initialise_pot_1(int value);
        virtual void process_new_pot_0_value(int value);
        virtual void process_new_pot_1_value(int value);
        void set_speed(float speed);
        void set_width(int width);
    private:
        LinearMapper mapper;
        float map_pot_0_value(int value);
        void map_pot_1_value(int value);
}   