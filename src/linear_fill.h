#ifndef LINEAR_FILL_H
#define LINEAR_FILL_H

#include "mode.h"
#include "constants.h"

class LinearFill: public Mode {
    public:
        LinearFill();
        LinearFill(CRGB* leds_);
        virtual void initialise(unsigned long current_millis);
        virtual void update(unsigned long current_millis);
        virtual void pot_0(uint16_t value);
        virtual void pot_1(uint16_t value);
        virtual void pot_2(uint16_t value);
    private:
        void constructor_defaults();
        int num_lit;
        int hue;
        int saturation;
};

#endif