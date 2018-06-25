#ifndef RAINBOW_LOOP_H
#define RAINBOW_LOOP_H

#include <Arduino.h>
#include "mode_base.h"
#include "constants.h"
#include "unit_offset.h"

class RainbowLoop: public Mode {
    public:
        RainbowLoop();
        RainbowLoop(CRGB* leds_);
        void update();
        void initialise();
        void apply_to_leds();
        void initialise_pot_0(int value);
        void initialise_pot_1(int value);
        void process_new_pot_0_value(int value);
        void process_new_pot_1_value(int value);
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