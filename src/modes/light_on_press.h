#ifndef LIGHT_ON_PRESS_H
#define LIGHT_ON_PRESS_H

#include <Arduino.h>
#include "mode_base.h"
#include "constants.h"

class LightOnPress: public Mode {
    public:
        LightOnPress();
        LightOnPress(CRGB* leds_);
        void apply_to_leds();
        void initialise_button_0(byte state);
        void button_0_pressed();
        void button_0_released();
    private:
        void constructor_defaults();
        byte button_state;
};

#endif