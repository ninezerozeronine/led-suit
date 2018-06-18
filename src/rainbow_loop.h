#ifndef RAINBOW_LOOP_H
#define RAINBOW_LOOP_H

#include <Arduino.h>
#include "mode.h"
#include "constants.h"
#include "unit_offset.h"

class RainbowLoop: public Mode {
    public:
        RainbowLoop();
        RainbowLoop(CRGB* leds_);
        virtual void update(unsigned long current_millis);
        virtual void initialise(unsigned long current_millis);
        virtual void initialise_pot_0(int value);
        virtual void initialise_pot_1(int value);
        virtual void process_new_pot_0_value(int value);
        virtual void process_new_pot_1_value(int value);
        void set_speed(float speed);
        void set_width(int width);
    private:
        void constructor_defaults();
        float map_pot_0_value(int value);
        int map_pot_1_value(int value);
        int output_to_pattern(int output, int length);
        float pattern_to_unit(int position, int length);
        CHSV unit_to_rainbow(float position);

        UnitOffset unit_offset;
        int width;
        float base_speed;
};

#endif