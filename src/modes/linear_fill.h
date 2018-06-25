#ifndef LINEAR_FILL_H
#define LINEAR_FILL_H

#include <Arduino.h>
#include "mode_base.h"
#include "constants.h"

class LinearFill: public Mode {
    public:
        LinearFill();
        LinearFill(CRGB* leds_);
        void apply_to_leds();
        void initialise_pot_0(int value);
        void initialise_pot_1(int value);
        void initialise_pot_2(int value);
        void process_new_pot_0_value(int value);
        void process_new_pot_1_value(int value);
        void process_new_pot_2_value(int value);
    private:
        void constructor_defaults();
        int map_pot_0_value(int value);
        int map_pot_1_value(int value);
        int map_pot_2_value(int value);
        int num_lit;
        int hue;
        int saturation;
};

#endif