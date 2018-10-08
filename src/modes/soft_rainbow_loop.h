#ifndef SOFT_RAINBOW_LOOP_H
#define SOFT_RAINBOW_LOOP_H

#include "loop_mode_base.h"

class SoftRainbowLoop: public LoopModeBase {
    public:
        SoftRainbowLoop();
        SoftRainbowLoop(CRGB* leds_);
    private:
        CHSV pattern_colour_lookup(float position);
};

#endif