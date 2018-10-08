#include "perlin.h"

Perlin::Perlin() : Mode() {
    constructor_defaults();
}

Perlin::Perlin(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}

void Perlin::constructor_defaults() {
    scale = 1;
    z_speed = 1;
    current_z = 0;
    last_update = 0;
}

void Perlin::initialise() {
    last_update = millis();
}

void Perlin::update() {
    unsigned long current_millis = millis();
    int elapsed_millis = current_millis - last_update;
    current_z = current_z + (z_speed * elapsed_millis);
    last_update = current_millis;
}

void Perlin::apply_to_leds() {
    for (int index = 0; index < constants::NUM_LEDS; index++) {
        int x = pgm_read_byte_near(constants::LED_X_VALS + index) * scale;
        int y = pgm_read_byte_near(constants::LED_Y_VALS + index) * scale;
        leds[index].setHSV(inoise8(x, y, int(current_z)), 255, 255);
    }
}

void Perlin::initialise_pot_0(int value) {
    z_speed = map_pot_0_value(value);
}

void Perlin::initialise_pot_1(int value) {
    scale = map_pot_1_value(value);
}

void Perlin::process_new_pot_0_value(int value) {
    z_speed = map_pot_0_value(value);
}

void Perlin::process_new_pot_1_value(int value) {
    scale = map_pot_1_value(value);
}


float Perlin::map_pot_0_value(int value) {
    return float(value) / 1023.0;
}

int Perlin::map_pot_1_value(int value) {
    return map(value, 0, 1023, 1, 20);
}
