#ifndef STREAKERS_H
#define STREAKERS_H

#define NUM_STREAKERS 10
#define FADE_AMOUNT 1
#define FADE_INTERVAL 10

#include <Arduino.h>
#include "mode_base.h"
#include "constants.h"

class Streakers: public Mode {
    public:
        Streakers();
        Streakers(CRGB* leds_);
        void apply_to_leds();
        void initialise_pot_0(int value);
        void initialise_pot_1(int value);
        void process_new_pot_0_value(int value);
        void process_new_pot_1_value(int value);

    private:
        unsigned long last_update;
        Streaker streakers[NUM_STREAKERS];

        void constructor_defaults();
        void set_speed(float speed);
        void set_hue(byte hue);
        float map_to_speed(int pot_value);
        byte map_to_hue(int pot_value);
};

#endif