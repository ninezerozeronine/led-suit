#include "streakers.h"

Streakers::Streakers() : Mode() {
    constructor_defaults();
}

Streakers::Streakers(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}

void Streakers::constructor_defaults() {
    last_update = 0;
    fade_amount = 4;
    fade_interval = 10;
    for (int index = 0; index < NUM_STREAKERS; index++) {
        streakers[index].set_leds(leds);
    }
}

void Streakers::initialise() {
    for (int index = 0; index < constants::NUM_LEDS; index++) {
        leds[index] = CRGB::Black;
    }
    last_update = millis();
    for (int index = 0; index < NUM_STREAKERS; index++) {
        streakers[index].initialise();
    }
}

void Streakers::update() {
    for (int index = 0; index < NUM_STREAKERS; index++) {
        streakers[index].update();
    }
}

void Streakers::apply_to_leds() {
    // Fade all the points
    unsigned long elapsed_millis = millis() - last_update;
    if (elapsed_millis > fade_interval) {
        for(int index = 0; index < constants::NUM_LEDS; index++) {
            leds[index].fadeToBlackBy(fade_amount);
        }
    }

    // Apply colour to points
    for (int index = 0; index < NUM_STREAKERS; index++) {
        streakers[index].apply_to_leds();
    }

}

void Streakers::set_speed(float speed) {
    for (int index = 0; index < NUM_STREAKERS; index++) {
        streakers[index].set_speed(speed);
        streakers[index].randomise_speed();
    }
}

void Streakers::set_hue(byte hue) {
    for (int index = 0; index < NUM_STREAKERS; index++) {
        streakers[index].set_hue(hue);
    }
}

void Streakers::initialise_pot_0(int pot_value) {
    set_speed(map_to_speed(pot_value));
}

void Streakers::initialise_pot_1(int pot_value) {
    set_hue(map_to_hue(pot_value));
}

void Streakers::initialise_pot_2(int pot_value) {
    fade_amount = map_to_fade_amount(pot_value);
}

void Streakers::initialise_pot_3(int pot_value) {
    fade_interval = map_to_fade_interval(pot_value);
}

void Streakers::process_new_pot_0_value(int value) {
    set_speed(map_to_speed(value));
}

void Streakers::process_new_pot_1_value(int value) {
    set_hue(map_to_hue(value));
}

void Streakers::process_new_pot_2_value(int pot_value) {
    fade_amount = map_to_fade_amount(pot_value);
}

void Streakers::process_new_pot_3_value(int pot_value) {
    fade_interval = map_to_fade_interval(pot_value);
}

float Streakers::map_to_speed(int pot_value) {
    return (float(pot_value) / float(1023)) * 0.04;
}

byte Streakers::map_to_hue(int pot_value) {
    return map(pot_value, 0, 1023, 0, 255);
}

byte Streakers::map_to_fade_amount(int pot_value) {
    return map(pot_value, 0, 1023, 0, 40);
}

byte Streakers::map_to_fade_interval(int pot_value) {
    return map(pot_value, 0, 1023, 0, 20);
}









