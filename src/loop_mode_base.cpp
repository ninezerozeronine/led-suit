#include "loop_mode_base.h"

LoopModeBase::LoopModeBase() : Mode() {
    constructor_defaults();
}

LoopModeBase::LoopModeBase(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}

void LoopModeBase::constructor_defaults(){
    current_mode = 0;
    base_speed = 0;
    set_pattern_width(255);
}

void LoopModeBase::initialise() {
    unit_offset.init();
}

void LoopModeBase::initialise_pot_0(int value) {
    set_speed(map_pot_0_value(value));
}

void LoopModeBase::initialise_pot_1(int value) {
    set_pattern_width(map_pot_1_value(value));
}

void LoopModeBase::button_0_pressed() {
    set_next_mode();
}

void LoopModeBase::update() {
    unit_offset.update();
}

void LoopModeBase::apply_to_leds_vert() {
    for (int index = 0; index < constants::NUM_LEDS; index++) {
        int pattern_pos = output_to_pattern(pgm_read_byte_near(constants::LED_Y_VALS + index));
        float unit_position = pattern_to_unit(pattern_pos);
        float offset_unit = unit_offset.apply_offset(unit_position);
        CHSV colour = pattern_colour_lookup(offset_unit);
        leds[index] = colour;
    }
}


void LoopModeBase::apply_to_leds_vert_split() {
    // Split the pattern in the middle and mirror it, e.g. if there were 8 positions:
    // 7 -> 3
    // 6 -> 2
    // 5 -> 1
    // 4 -> 0
    // 3 -> 1
    // 2 -> 2
    // 1 -> 3
    // 0 -> 4
    for (int index = 0; index < constants::NUM_LEDS; index++) {
        int output_pos = pgm_read_byte_near(constants::LED_Y_VALS + index);
        int remapped_pos = 0;
        if (output_pos <= 127) {
            remapped_pos = 128 - output_pos;
        } else {
            remapped_pos = output_pos - 128;
        }
        int pattern_pos = output_to_pattern(remapped_pos);
        float unit_position = pattern_to_unit(pattern_pos);
        float offset_unit = unit_offset.apply_offset(unit_position);
        CHSV colour = pattern_colour_lookup(offset_unit);
        leds[index] = colour;
    }
}

void LoopModeBase::apply_to_leds_horiz() {
    for (int index = 0; index < constants::NUM_LEDS; index++) {
        int pattern_pos = output_to_pattern(pgm_read_byte_near(constants::LED_X_VALS + index));
        float unit_position = pattern_to_unit(pattern_pos);
        float offset_unit = unit_offset.apply_offset(unit_position);
        CHSV colour = pattern_colour_lookup(offset_unit);
        leds[index] = colour;
    }
}


void LoopModeBase::apply_to_leds_horiz_split() {
    // Split the pattern in the middle and mirror it, e.g. if there were 8 positions:
    // 7 -> 3
    // 6 -> 2
    // 5 -> 1
    // 4 -> 0
    // 3 -> 1
    // 2 -> 2
    // 1 -> 3
    // 0 -> 4
    for (int index = 0; index < constants::NUM_LEDS; index++) {
        int output_pos = pgm_read_byte_near(constants::LED_X_VALS + index);
        int remapped_pos = 0;
        if (output_pos <= 127) {
            remapped_pos = 128 - output_pos;
        } else {
            remapped_pos = output_pos - 128;
        }
        int pattern_pos = output_to_pattern(remapped_pos);
        float unit_position = pattern_to_unit(pattern_pos);
        float offset_unit = unit_offset.apply_offset(unit_position);
        CHSV colour = pattern_colour_lookup(offset_unit);
        leds[index] = colour;
    }
}

void LoopModeBase::apply_to_leds(){
    switch(current_mode){
        case 0:
            apply_to_leds_vert();
            break;
        case 1:
            apply_to_leds_vert_split();
            break;
        case 2:
            apply_to_leds_horiz();
            break;
        case 3:
            apply_to_leds_horiz_split();
            break;
    }
}

void LoopModeBase::set_speed(float speed) {
    base_speed = speed;
    unit_offset.set_speed((base_speed/float(pattern_width)) * 0.8);
    // unit_offset.set_speed(base_speed * 0.01);
}

void LoopModeBase::set_pattern_width(int pattern_width_) {
    pattern_width = pattern_width_;
    set_speed(base_speed);
}

void LoopModeBase::process_new_pot_0_value(int value){
    set_speed(map_pot_0_value(value));
}

void LoopModeBase::process_new_pot_1_value(int value){
    set_pattern_width(map_pot_1_value(value));
}

float LoopModeBase::map_pot_0_value(int value) {
    int potentiometer_max = 1023;
    int deadband_width = 30;
    int mid_point = potentiometer_max/2;
    int dead_min = mid_point - deadband_width/2;
    int dead_max = mid_point + deadband_width/2;
    float speed = 0;
    if (value < dead_min) {
        int dist_from_dead_min = dead_min - value;
        float normalised = float(dist_from_dead_min) / float(dead_min);
        speed = -1.0 * normalised;
    } else if (value > dead_max) {
        int dist_from_dead_max = value - dead_max;
        speed = float(dist_from_dead_max) / float(potentiometer_max - dead_max);
    }
    return speed;
}

int LoopModeBase::map_pot_1_value(int value) {
    // Pattern Width
    return map(value, 0, 1023, 80, 2000);
}

int LoopModeBase::output_to_pattern(int output) {
    return output % pattern_width;
}

float LoopModeBase::pattern_to_unit(int position) {
    return float(position) / float(pattern_width);
}

void LoopModeBase::set_next_mode() {
    current_mode = (current_mode + 1) % NUM_LOOP_MODES;
}