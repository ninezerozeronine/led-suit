#include "light_on_press.h"

LightOnPress::LightOnPress() {
    constructor_defaults();
}

LightOnPress::LightOnPress(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}

void LightOnPress::constructor_defaults(){
    button_state = LOW;
}

void LightOnPress::initialise(unsigned long current_millis) {

}

void LightOnPress::initialise_button_0(byte state){
    button_state = state;
}

void LightOnPress::update(unsigned long current_millis){
    for (int index = 0; index < constants::NUM_LEDS; index++) {
        if (button_state == HIGH) {
            leds[index] = CRGB::White;
        } else {
            leds[index] = CRGB::Black;
        }
    }
}

void LightOnPress::button_0_pressed(){
    button_state = HIGH;
}

void LightOnPress::button_0_released(){
    button_state = LOW;
}


