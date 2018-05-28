#include "linear_fill.h"

LinearFill::LinearFill() {
    constructor_defaults();
}


LinearFill::LinearFill(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}


void LinearFill::initialise(unsigned long current_millis) {

}


void LinearFill::update(unsigned long current_millis){
    for (int index = 0; index < NUM_LEDS; index++) {
        if (index < num_lit) {
            leds[index].setHSV(hue, saturation, 255);
        } else {
            leds[index] = CRGB::Black;
        }
    }
}


void LinearFill::pot_0(uint16_t value){
    num_lit = map(value, 0, 1023, 0, NUM_LEDS);
}


void LinearFill::pot_1(uint16_t value){
    hue = map(value, 0, 1023, 0, 255);
}


void LinearFill::pot_2(uint16_t value){
    saturation = map(value, 0, 1023, 0, 255);
}


void LinearFill::constructor_defaults(){
    num_lit = saturation = hue = 0;
}