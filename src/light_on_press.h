#ifndef LIGHT_ON_PRESS_H
#define LIGHT_ON_PRESS_H

#include <Arduino.h>
#include "mode.h"
#include "constants.h"

class LightOnPress: public Mode {
    public:
        LightOnPress();
        LightOnPress(CRGB* leds_);
        virtual void update(unsigned long current_millis);
        virtual void initialise(unsigned long current_millis);
        virtual void initialise_button_0(bool state);
        virtual void button_0_pressed();
        virtual void button_0_released();
    private:
        void constructor_defaults();
        bool button_pressed;
};

#endif