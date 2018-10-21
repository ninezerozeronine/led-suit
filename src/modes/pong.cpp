#include "pong.h"

Pong::Pong() : Mode() {
    constructor_defaults();
}

Pong::Pong(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}

void Pong::initialise() {
    last_update = millis();
    switch_to_wait_to_start();
}

void Pong::initialise_pot_0(int value) {
    set_zone_size(map_pot_0_value(value));
}

void Pong::initialise_pot_1(int value) {
    top_hue = map_pot_to_byte(value);
}
void Pong::initialise_pot_2(int value) {
    bottom_hue = map_pot_to_byte(value);
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
        set_zone_size(map_pot_0_value(value));
    }
}

void Pong::process_new_pot_1_value(int value) {
    if (game_mode == WAIT_TO_START) {
        set_top_hue(map_pot_to_byte(value));
    }
}

void Pong::process_new_pot_2_value(int value) {
    if (game_mode == WAIT_TO_START) {
        set_bottom_hue(map_pot_to_byte(value));
    }
}

void Pong::button_1_pressed() {
    top_was_pressed = true;
    top_is_pressed = true;
}

void Pong::button_2_pressed() {
    bottom_was_pressed = true;
    bottom_is_pressed = true;
}

void Pong::button_1_released() {
    top_is_pressed = false;
}

void Pong::button_2_released() {
    bottom_is_pressed = false;
}

void Pong::update() {
    current_millis = millis();
    elapsed_millis = current_millis - last_update;

    switch(game_mode){
        case WAIT_TO_START:
            update_wait_to_start();
            break;
        case COUNTDOWN:
            update_countdown();
            break;
        case PLAYING:
            update_playing();
            break;
        case TOP_WON:
            update_top_won();
            break;
        case BOTTOM_WON:
            update_bottom_won();
            break;
    }

    // Reset button press detection
    top_was_pressed = false;
    bottom_was_pressed = false;

    last_update = current_millis;
}

void Pong::apply_to_leds() {
    switch(game_mode){
        case WAIT_TO_START:
            draw_wait_to_start();
            break;
        case COUNTDOWN:
            draw_countdown();
            break;
        case PLAYING:
            draw_playing();
            break;
        case TOP_WON:
            draw_top_won();
            break;
        case BOTTOM_WON:
            draw_bottom_won();
            break;
    }
}


void Pong::constructor_defaults(){
    last_update = 0;
    elapsed_millis = 0;
    ball_speed = 0;
    ball_position = float(constants::GRID_HEIGHT)/2.0;
    ball_blink_state = true;
    top_zone_min = 0;
    top_zone_max = 0;
    bottom_zone_min = 0;
    bottom_zone_max = 0;
    countdown_begin = 0;
    win_begin = 0;
    top_hue = 0;
    bottom_hue = 180;
    both_pressed_begin = 0;

    game_mode = WAIT_TO_START;
    both_pressed = false;
    top_was_pressed = false;
    top_is_pressed = false;
    bottom_was_pressed = false;
    bottom_is_pressed = false;
}

int Pong::map_pot_0_value(int value) {
    float percentage = float(value)/1023.0;
    return (ZONE_PERCENT_MIN + (1.0 - percentage)) + (ZONE_PERCENT_MAX * percentage);
}

byte Pong::map_pot_to_byte(int pot_value) {
    return map(pot_value, 0, 1023, 0, 255);
}

void Pong::set_zone_size(float percentage) {
    top_zone_min = 0.0;
    top_zone_max = (constants::GRID_HEIGHT * 0.5) * percentage;

    bottom_zone_min = constants::GRID_HEIGHT - top_zone_max;
    bottom_zone_max = constants::GRID_HEIGHT;
}

void Pong::set_top_hue(byte hue) {
    top_hue = hue;
}

void Pong::set_bottom_hue(byte hue) {
    bottom_hue = hue;
}

void Pong::update_wait_to_start() {
    // Calculate blink
    int blink_period_progress = current_millis % 1000;
    if (blink_period_progress > 500) {
        ball_blink_state = true;
    } else {
        ball_blink_state = false;
    }

    // Test if both buttons have been pressed for long enough
    if (top_is_pressed and bottom_is_pressed) {
        if (both_pressed) {
            if (current_millis - both_pressed_begin > 1000) {
                switch_to_countdown();
            }
        } else {
            both_pressed = true;
            both_pressed_begin = current_millis;
        }
    } else {
        both_pressed = false;
    }
}

void Pong::update_countdown() {
    if ((current_millis - countdown_begin) > 2000) {
        switch_to_playing();
    }
}

void Pong::update_playing() {
    if (ball_position < 0) {
        switch_to_bottom_won();
    }

    if (ball_position > float(constants::GRID_HEIGHT)) {
        switch_to_top_won();
    }

    // Check if top has returned
    if (ball_speed < 0) {
        if (ball_position < top_zone_max) {
            if (top_was_pressed) {
                return_ball();
            }
        }
    }

    // Check if bottom has returned
    if (ball_speed > 0) {
        if (ball_position > bottom_zone_min) {
            if (bottom_was_pressed) {
                return_ball();
            }
        }
    }

    // Update ball position
    ball_position = ball_position + (ball_speed * elapsed_millis);
}

void Pong::update_top_won() {
    if ((current_millis - win_begin) > 2000) {
        switch_to_wait_to_start();
    }
}

void Pong::update_bottom_won() {
    if ((current_millis - win_begin) > 2000) {
        switch_to_wait_to_start();
    }
}

void Pong::draw_wait_to_start() {
    FastLED.showColor(CRGB::Black);
    draw_endzones();
    if (ball_blink_state) {
        draw_ball();
    }

}

void Pong::draw_countdown() {
    draw_endzones();
    draw_ball();
}

void Pong::draw_playing() {
    if (elapsed_millis > FADE_INTERVAL) {
        for(int index = 0; index < constants::NUM_LEDS; index++) {
            leds[index].fadeToBlackBy(FADE_AMOUNT);
        }
    draw_endzones();
    draw_ball();
}

void Pong::draw_top_won() {

}

void Pong::set_all_black() {

}

void Pong::draw_bottom_won() {

}

void Pong::fade_all() {

}

void Pong::draw_endzones() {

}

void Pong::draw_ball() {

}
