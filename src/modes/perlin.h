#ifndef PERLIN_H
#define PERLIN_H

#include <Arduino.h>
#include "mode_base.h"
#include "constants.h"

class Perlin: public Mode {
    public:
        Perlin();
        Perlin(CRGB* leds_);
        void apply_to_leds();
        void initialise();
        void update();
        void initialise_pot_0(int value);
        void initialise_pot_1(int value);
        void process_new_pot_0_value(int value);
        void process_new_pot_1_value(int value);
    private:
        void constructor_defaults();
        float map_pot_0_value(int value);
        int map_pot_1_value(int value);

        unsigned long last_update;
        int scale;
        float z_speed;
        float current_z;
};

#endif