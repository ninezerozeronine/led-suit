#ifndef STREAKER_H
#define STREAKER_H

#include <Arduino.h>
#include <FastLED.h>
#include "constants.h"

class Streaker {
    public:
        Streaker();
        void constructor_defaults();
        void set_leds(CRGB* _leds);
        void set_speed(float _speed);
        void randomise_speed();
        void set_hue(byte _hue);
        void set_width(byte _width);
        void set_height(byte _height);
        void initialise();
        void update();
        void apply_to_leds();

    private:
        CRGB * leds;
        unsigned long last_update;
        float speed;
        byte hue;
        byte width;
        byte height;
        byte column;
        float y;

        void move_to_new_column();
};

#endif