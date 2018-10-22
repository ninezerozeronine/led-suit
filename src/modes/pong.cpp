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
    set_bottom_hue(map_pot_to_byte(value));
}
void Pong::initialise_pot_2(int value) {
    set_top_hue(map_pot_to_byte(value));
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
        set_bottom_hue(map_pot_to_byte(value));
    }
}

void Pong::process_new_pot_2_value(int value) {
    if (game_mode == WAIT_TO_START) {
        set_top_hue(map_pot_to_byte(value));
    }
}

void Pong::button_0_pressed() {
    Serial.println("button_1_pressed");
    top_was_pressed = true;
    top_is_pressed = true;
}

void Pong::button_1_pressed() {
    Serial.println("button_2_pressed");
    bottom_was_pressed = true;
    bottom_is_pressed = true;
}

void Pong::button_0_released() {
    top_is_pressed = false;
}

void Pong::button_1_released() {
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
    top_hue_inverse = 128;
    bottom_hue = 100;
    bottom_hue_inverse = 228;
    both_pressed_begin = 0;

    game_mode = WAIT_TO_START;
    both_pressed = false;
    top_was_pressed = false;
    top_is_pressed = false;
    bottom_was_pressed = false;
    bottom_is_pressed = false;
}

float Pong::map_pot_0_value(int value) {
    float percentage = float(value)/1023.0;
    return (ZONE_PERCENT_MIN * (1.0 - percentage)) + (ZONE_PERCENT_MAX * percentage);
}

byte Pong::map_pot_to_byte(int pot_value) {
    return map(pot_value, 0, 1023, 0, 255);
}

void Pong::set_zone_size(float percentage) {
    Serial.println(percentage);
    top_zone_min = 0.0;
    top_zone_max = (float(constants::GRID_HEIGHT) * 0.5) * percentage;

    bottom_zone_min = float(constants::GRID_HEIGHT) - top_zone_max;
    bottom_zone_max = float(constants::GRID_HEIGHT);

    Serial.print(top_zone_min);
    Serial.print(", ");
    Serial.print(top_zone_max);
    Serial.print(" ");
    Serial.print(bottom_zone_min);
    Serial.print(", ");
    Serial.println(bottom_zone_max);
}

void Pong::set_top_hue(byte hue) {
    top_hue = hue;
    top_hue_inverse = (top_hue + 128) % 256;
}

void Pong::set_bottom_hue(byte hue) {
    bottom_hue = hue;
    bottom_hue_inverse = (bottom_hue + 128) % 256;
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

void Pong::return_ball() {
    ball_speed *= -1.2;
}

void Pong::draw_wait_to_start() {
    for(int index = 0; index < constants::NUM_LEDS; index++) {
        leds[index] = CRGB::Black;
    }
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
    }
    draw_endzones();
    draw_ball();
}

void Pong::draw_top_won() {
    for(int index = 0; index < constants::NUM_LEDS; index++) {
        leds[index] = (CHSV(top_hue, 255, 255));
    }
}


void Pong::draw_bottom_won() {
    for(int index = 0; index < constants::NUM_LEDS; index++) {
        leds[index] = (CHSV(bottom_hue, 255, 255));
    }
}


void Pong::draw_endzones() {
    // Draw top
    for (int row = int(top_zone_min); row < int(top_zone_max); row++) {
        for (int column = 0; column < constants::GRID_WIDTH; column++) {
            int index = (row * constants::GRID_WIDTH) + column;
            if (top_is_pressed) {
                leds[index] = CHSV(top_hue_inverse, 255, 255);
            } else {
                leds[index] = CHSV(top_hue, 255, 255);
            }
        }
    }

    // Draw bottom
    for (int row = int(bottom_zone_min); row < int(bottom_zone_max); row++) {
        for (int column = 0; column < constants::GRID_WIDTH; column++) {
            int index = (row * constants::GRID_WIDTH) + column;
            if (bottom_is_pressed) {
                leds[index] = CHSV(bottom_hue_inverse, 255, 255);
            } else {
                leds[index] = CHSV(bottom_hue, 255, 255);
            }
        }
    }
}

void Pong::draw_ball() {
    int row = int(ball_position);
    for (int column = 0; column < constants::GRID_WIDTH; column++) {
        int index = (row * constants::GRID_WIDTH) + column;
        leds[index] = CRGB::White;
    }
}


void Pong::switch_to_wait_to_start() {
    Serial.println(" -> WAIT_TO_START");
    game_mode = WAIT_TO_START;
    ball_position = constants::GRID_HEIGHT / 2.0;
}

void Pong::switch_to_countdown() {
    Serial.println(" -> COUNTDOWN");
    game_mode = COUNTDOWN;
    countdown_begin = current_millis;
}

void Pong::switch_to_playing() {
    Serial.println(" -> PLAYING");
    game_mode = PLAYING;
    float mult = 1.0;
    if (random(1)) {
        float mult = -1.0;
    }
    ball_speed = 0.0025 * mult;
}

void Pong::switch_to_top_won() {
    Serial.println(" -> TOP_WON");
    game_mode = TOP_WON;
    win_begin = current_millis;
}

void Pong::switch_to_bottom_won() {
    Serial.println(" -> BOTTOM_WON");
    game_mode = BOTTOM_WON;
    win_begin = current_millis;
}
