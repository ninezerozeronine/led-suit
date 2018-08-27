#include "streakers.h"

Streakers::Streakers() : Mode() {
    constructor_defaults();
}

Streakers::Streakers(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}

void Streakers::constructor_defaults() {
    last_update = 0;
    for (int index = 0; index < constants::NUM_STREAKERS; index++) {
        streakers[index].set_leds(leds);

    }
}

void Streakers::initialise() {
    last_update = millis();
    for (int index = 0; index < constants::NUM_STREAKERS; index++) {
        streakers[index].initialise();
    }
}

void Streakers::apply_to_leds() {
    // Fade all the points
    unsigned long elapsed_millis = millis() - last_update;
    if (elapsed_millis > FADE_INTERVAL) {
        for(int index = 0; index < NUM_LEDS; index++) {
            leds[index].fadeToBlackBy(FADE_AMOUNT);
        }
    }

    // Apply colour to points
    for (int index = 0; index < constants::NUM_STREAKERS; index++) {
        streakers[index].apply_to_leds();
    }

}

void Streakers::set_speed(float speed) {

}

void Streakers::set_colour(byte hue) {

}

void Streakers::initialise_pot_0(int value) {

}

void Streakers::initialise_pot_1(int value) {

}

void Streakers::process_new_pot_0_value(int value) {

}

void Streakers::process_new_pot_1_value(int value) {

}

float Streakers::map_to_speed(int pot_value) {

}

byte Streakers::map_to_hue(int pot_value) {

}












