#include "pong.h"

Pong::Pong() : Mode() {
    constructor_defaults();
}

Pong::Pong(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}

void Pong::initialise() {
    last_update = millis();
    game_mode = WAIT_TO_START;
}

void Pong::initialise_pot_0(int value) {
    zone_size = map_pot_0_value(value);
}

void Pong::initialise_pot_1(int value) {
    top_hue = map_pot_to_byte(pot_value);
}
void Pong::initialise_pot_2(int value) {
    bottom_hue = map_pot_to_byte(pot_value);
}

void Pong::initialise_button_1(byte state) {
    if (state == 0) {
        top_is_pressed = false;
    } else {
        top_is_pressed = true;
    }
}
void Pong::initialise_button_2(byte state) {
    if (state == 0) {
        bottom_is_pressed = false;
    } else {
        bottom_is_pressed = true;
    }
}

void Pong::process_new_pot_0_value(int value) {
    if (game_mode == WAIT_TO_START) {
        zone_size = map_pot_0_value(value);
    }
}

void Pong::process_new_pot_1_value(int value) {
    if (game_mode == WAIT_TO_START) {
        top_hue = map_pot_to_byte(value);
    }
}

void Pong::process_new_pot_2_value(int value) {
    if (game_mode == WAIT_TO_START) {
        bottom_hue = map_pot_to_byte(value);
    }
}

void Pong::button_1_pressed() {
    
}

void Pong::button_2_pressed() {

}

void Pong::button_1_released() {

}

void Pong::button_2_released() {

}

void Pong::update() {

}

void Pong::apply_to_leds() {

}


void Pong::constructor_defaults(){
    last_update = 0;
    ball_speed = 0;
    ball_position = float(constants::GRID_HEIGHT)/2.0;
    zone_size = 0.25
    countdown_time = 0;
    win_wipe_progress = 0;
    top_hue = 0;
    bottom_hue = 180;
    both_pressed_begin = 0;

    game_mode WAIT_TO_START;
    top_was_pressed = false;
    top_is_pressed = false;
    bottom_was_pressed = false;
    bottom_is_pressed = false;
}






void Pong::process_new_pot_0_value(int value) {
    
}

int Pong::map_pot_0_value(int value) {
    float percentage = float(value)/1023.0;
    return (ZONE_SIZE_MIN + (1.0 - percentage)) + (ZONE_SIZE_MAX * percentage);
}

byte Pong::map_pot_to_byte(int pot_value) {
    return map(pot_value, 0, 1023, 0, 255);
}