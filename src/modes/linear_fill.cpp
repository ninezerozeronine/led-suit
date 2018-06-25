#include "linear_fill.h"

LinearFill::LinearFill() {
    constructor_defaults();
}

LinearFill::LinearFill(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}

void LinearFill::constructor_defaults(){
    num_lit = saturation = hue = 0;
}

void LinearFill::apply_to_leds(){
    for (int index = 0; index < constants::NUM_LEDS; index++) {
        if (index < num_lit) {
            leds[index].setHSV(hue, saturation, 255);
        } else {
            leds[index] = CRGB::Black;
        }
    }
}

void LinearFill::initialise_pot_0(int value) {
    num_lit = map_pot_0_value(value);
}

void LinearFill::initialise_pot_1(int value) {
    hue = map_pot_1_value(value);
}

void LinearFill::initialise_pot_2(int value) {
    saturation = map_pot_2_value(value);
}

void LinearFill::process_new_pot_0_value(int value){
    num_lit = map_pot_0_value(value);
}

void LinearFill::process_new_pot_1_value(int value){
    hue = map_pot_1_value(value);
}

void LinearFill::process_new_pot_2_value(int value){
    saturation = map_pot_2_value(value);
}

int LinearFill::map_pot_0_value(int value) {
    return map(value, 0, 1023, 0, constants::NUM_LEDS);
}

int LinearFill::map_pot_1_value(int value) {
    return map(value, 0, 1023, 0, 255);
}

int LinearFill::map_pot_2_value(int value) {
    return map(value, 0, 1023, 0, 255);
}