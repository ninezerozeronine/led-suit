#ifndef LINEAR_FILL_H
#define LINEAR_FILL_H

#include <Arduino.h>
#include "mode.h"
#include "constants.h"

class LinearFill: public Mode {
    public:
        LinearFill();
        LinearFill(CRGB* leds_);
        virtual void initialise(unsigned long current_millis);
        virtual void update(unsigned long current_millis);
        virtual void initialise_pot_0(int value);
        virtual void initialise_pot_1(int value);
        virtual void initialise_pot_2(int value);
        virtual void process_new_pot_0_value(int value);
        virtual void process_new_pot_0_value(int value);
        virtual void process_new_pot_0_value(int value);
    private:
        void constructor_defaults();
        int num_lit;
        int hue;
        int saturation;
};

#endif