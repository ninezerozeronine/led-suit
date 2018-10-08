#ifndef HARD_RAINBOW_LOOP_H
#define HARD_RAINBOW_LOOP_H

#include "loop_mode_base.h"

class HardRainbowLoop: public LoopModeBase {
    public:
        HardRainbowLoop();
        HardRainbowLoop(CRGB* leds_);
        void initialise_pot_2(int value);
        void process_new_pot_2_value(int value);
        void set_num_bars(byte num_bars_);
        
    private:
        CHSV pattern_colour_lookup(float position);
        byte map_pot_2_value(int value);
        void constructor_defaults();

        byte num_bars;
};

#endif