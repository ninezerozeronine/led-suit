#include "streaker.h"

Streaker::Streaker() {
    constructor_defaults();
}

void Streaker::constructor_defaults() {
    leds = NULL;
    speed = 0.001;
    hue = 0;
    width = constants::GRID_WIDTH;
    height = constants::GRID_HEIGHT;
    last_update = 0;

    y = random(height);
    move_to_new_column();
    randomise_speed();
}


void Streaker::set_leds(CRGB* _leds) {
    leds = _leds;
}

void Streaker::set_speed(float _speed) {
    speed = _speed;
}

void Streaker::randomise_speed() {
    // Speed will vary up or down by 20%
    int amount = random(40);
    amount -= 20;
    float percentage = float(amount)/100;
    speed = speed * percentage;
}

void Streaker::set_hue(byte _hue) {
    hue = _hue;
}

void Streaker::set_width(byte _width) {
    width = _width;
}

void Streaker::set_height(byte _height) {
    height = _height;
}

void Streaker::initialise() {
    last_update = millis();
}

void Streaker::update() {
    unsigned long elapsed_millis = millis() - last_update;
    y += float(elapsed_millis) * speed;
    if (y > float(height)) {
        y = 0;
        move_to_new_column();
    }
}

void Streaker::move_to_new_column() {
    column = random(width);
}

void Streaker::apply_to_leds() {
    int current_row = int(y);
    int index = (current_row * width) + column;
    int led_index = pgm_read_word_near(constants::LED_GRID_INDECIES + index);
    if (led_index > 0) {
        leds[led_index] = CHSV(hue, 255, 255);
    }
}


































