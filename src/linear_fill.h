#ifndef LINEAR_FILL_H
#define LINEAR_FILL_H

#include "mode.h"
#include "constants.h"

class LinearFill: public Mode {
    public:
        LinearFill();
        LinearFill(CRGB* leds_) : Mode(leds_);
        void initialise(unsigned long current_millis);
        void update(unsigned long current_millis);
        void pot_0(int value);
        void pot_1(int value);
        void pot_2(int value);
    private:
        void constructor_defaults();
        int hue;
        int saturation;
        int num_lit;
}

#endif