#include "rainbow_loop.h"

RainbowLoop::RainbowLoop() {
    constructor_defaults();
}

RainbowLoop::RainbowLoop(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}

void RainbowLoop::constructor_defaults(){
    base_speed = 0;
    set_width(255);
}

void RainbowLoop::initialise(unsigned long current_millis) {
    unit_offset.init();
}

void RainbowLoop::initialise_pot_0(int value) {
    set_speed(map_pot_0_value(value));
}

void RainbowLoop::initialise_pot_1(int value) {
    set_width(map_pot_1_value(value));
}

void RainbowLoop::update(unsigned long current_millis) {
    unit_offset.update();
    for (int index = 0; index < constants::NUM_LEDS; index++) {
        int pattern_pos = output_to_pattern(pgm_read_byte_near(constants::LED_Y_VALS + index), width);
        float unit_position = pattern_to_unit(pattern_pos, width);
        float offset_unit = unit_offset.apply_offset(unit_position);
        CHSV colour = unit_to_rainbow(offset_unit);
        leds[index] = colour;
    }
}

void RainbowLoop::set_speed(float speed) {
    base_speed = speed;
    unit_offset.set_speed((base_speed/float(width)) * 0.8);
    // unit_offset.set_speed(base_speed * 0.01);
}

void RainbowLoop::set_width(int width_) {
    width = width_;
    set_speed(base_speed);
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
    float speed;
    if (value < dead_min) {
        int dist_from_dead_min = dead_min - value;
        float normalised = float(dist_from_dead_min) / float(dead_min);
        speed = -1.0 * normalised;
    } else if (value > dead_max) {
        int dist_from_dead_max = value - dead_max;
        speed = float(dist_from_dead_max) / float(1023 - dead_max);
    }
    return speed;
}

int RainbowLoop::map_pot_1_value(int value) {
    // Width
    return map(value, 0, 1023, 80, 2000);
}

int RainbowLoop::output_to_pattern(int output, int length) {
    return output % length;
}

float RainbowLoop::pattern_to_unit(int position, int length) {
    return float(position) / float(length);
}

CHSV RainbowLoop::unit_to_rainbow(float position) {
    // Rainbow
    // byte hue = 255 * position;
    // return CHSV(hue, 255, 255);

    // Harsh rainbow
    int num_stripes = 6;
    position = position * num_stripes;
    byte hue = 255.0/float(num_stripes) * int(position);
    return CHSV(hue, 255, 255);

    // Stripes
    // if (position > 0.5) {
    //     return CHSV(0,0,0);
    // } else {
    //     return CHSV(0,0,255);
    // }

    // Soft stripes
    // ((1.0 - lerp_value) * _min) + (lerp_value * _max);
    // if (position < 0.5) {
    //     float lerp_value = position * 2.0;
    //     byte value = ((1.0 - lerp_value) * 0) + (lerp_value * 255);
    //     return CHSV(0,0,value);
    // } else {
    //     float lerp_value = (position * 2.0) - 1;
    //     byte value = ((1.0 - lerp_value) * 255);
    //     return CHSV(0,0,value);
    // }
}