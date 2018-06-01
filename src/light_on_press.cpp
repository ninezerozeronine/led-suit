#include "light_on_press.h"

LightOnPress::LightOnPress() {
    constructor_defaults();
}


LightOnPress::LightOnPress(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}


void LightOnPress::initialise(unsigned long current_millis) {

}


void LightOnPress::update(unsigned long current_millis){
    for (int index = 0; index < constants::NUM_LEDS; index++) {
        if (button_pressed == true) {
            leds[index] = CRGB::White;
        } else {
            leds[index] = CRGB::Black;
        }
    }
}


void LightOnPress::button_0_pressed(){
    button_pressed = true;
}


void LightOnPress::button_0_released(){
    button_pressed = false;
}


void LightOnPress::constructor_defaults(){
    button_pressed = false;
}