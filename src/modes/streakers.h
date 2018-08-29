#ifndef STREAKERS_H
#define STREAKERS_H

#define NUM_STREAKERS 10
// In 255ths
#define FADE_AMOUNT 2
#define FADE_INTERVAL 10

#include <Arduino.h>
#include "mode_base.h"
#include "constants.h"
#include "streaker.h"

class Streakers: public Mode {
    public:
        Streakers();
        Streakers(CRGB* leds_);
        void initialise();
        void update();
        void apply_to_leds();
        void initialise_pot_0(int value);
        void initialise_pot_1(int value);
        void initialise_pot_2(int value);
        void initialise_pot_3(int value);
        void process_new_pot_0_value(int value);
        void process_new_pot_1_value(int value);
        void process_new_pot_2_value(int value);
        void process_new_pot_3_value(int value);

    private:
        byte fade_amount;
        byte fade_interval;
        unsigned long last_update;
        Streaker streakers[NUM_STREAKERS];

        void constructor_defaults();
        void set_speed(float speed);
        void set_hue(byte hue);
        void set_fade_amount(byte _fade_amount);
        void set_fade_interval(byte _interval);
        float map_to_speed(int pot_value);
        byte map_to_hue(int pot_value);
        byte map_to_fade_amount(int pot_value);
        byte map_to_fade_interval(int pot_value);
};

#endif