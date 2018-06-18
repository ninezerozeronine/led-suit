#include "rainbow_loop.h"

RainbowLoop::RainbowLoop() {
    constructor_defaults();
}

RainbowLoop::RainbowLoop(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}

void RainbowLoop::constructor_defaults(){
    set_speed(0);
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

        if (constants::LED_Y_VALS[index] > 128) {
            leds[index] = CHSV(0,255,255);
        } else {
            leds[index] = CHSV(128,255,255);
        }




        // int pattern_pos = output_to_pattern(constants::LED_Y_VALS[index], width);
        // float unit_position = pattern_to_unit(pattern_pos, width);
        // float offset_unit = unit_offset.apply_offset(unit_position);
        // Serial.println(offset_unit);
        // CHSV colour = unit_to_rainbow(offset_unit);
        // leds[index] = colour;
    }
}

void RainbowLoop::set_speed(float speed) {
    unit_offset.set_speed(speed);
}

void RainbowLoop::set_width(int width_) {
    width = width_;
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
    float max_speed = 0.005;
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
    return map(value, 0, 1023, 5, 255);
}

int RainbowLoop::output_to_pattern(int output, int length) {
    return output % length;
}

float RainbowLoop::pattern_to_unit(int position, int length) {
    return float(position) / float(length);
}

CHSV RainbowLoop::unit_to_rainbow(float position) {
    byte hue = 0;
    if (position > 0.5) {
        hue = 128;
    }
    return CHSV(hue, 255, 255);
}