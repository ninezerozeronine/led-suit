#include "rainbow_loop.h"

RainbowLoop::RainbowLoop() {
    constructor_defaults();
}


RainbowLoop::RainbowLoop(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}


void RainbowLoop::constructor_defaults(){
    set_speed(0);
    set_max_value(255);
}

void RainbowLoop::initialise(unsigned long current_millis) {

}


void RainbowLoop::initialise_pot_0(int value) {
    set_speed(map_pot_0_value(value));

}


void RainbowLoop::initialise_pot_1(int value) {
    set_width(map_pot_1_value(value))
    
}

void set_speed(float speed) {
    mapper.set_speed(speed);
}

void set_width(int width) {
    mapper.set_max_value(width);
}

void RainbowLoop::process_new_pot_0_value(int value){
    set_speed(map_pot_0_value(value));
}


void RainbowLoop::process_new_pot_1_value(int value){
    set_width(map_pot_1_value(value));
}


float RainbowLoop::map_pot_0_value(int value) {
    // Speed
    int dead_min = 500;
    int dead_max = 520;
    float max_speed = 0.01;
    float speed = 0;
    if (value < dead_min) {
        int dist_from_dead_min = dead_min - value;
        float normalised = float(dist_from_dead_min) / float(dead_min);
        speed = -1.0 * normalised * max_speed;
    } else if (value > dead_max) {
        int dist_from_dead_max = value - dead_max;
        float normalised = float(dist_from_dead_max) / float(1023 - dead_max);
        speed = normalised * max_speed;
    }
    return speed;
}


int RainbowLoop::map_pot_1_value(int value) {
    // Width
    return map(value, 0, 1023, 5, 100);
}

