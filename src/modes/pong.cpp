#include "pong.h"

Pong::Pong() : Mode() {
    constructor_defaults();
}

Pong::Pong(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}

void Pong::initialise() {
    last_update = millis();
    last_fade = millis();
    switch_to_wait_to_start();
    top_half_max_row = int((constants::GRID_HEIGHT - 1) / 2.0);
    bottom_half_min_row = top_half_max_row + 1;
}

void Pong::initialise_pot_0(int value) {
    set_bottom_zone_size(map_pot_to_unit(value));
}

void Pong::initialise_pot_1(int value) {
    set_top_zone_size(map_pot_to_unit(value));
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
        set_bottom_zone_size(map_pot_to_unit(value));
    }
}

void Pong::process_new_pot_1_value(int value) {
    if (game_mode == WAIT_TO_START) {
        set_top_zone_size(map_pot_to_unit(value));
    }
}

void Pong::button_0_pressed() {
    top_was_pressed = true;
    top_is_pressed = true;
    // int rounded_pos = round(ball_position);
    // Serial.print(top_zone_min);
    // Serial.print(", ");
    // Serial.println(top_zone_max);
    // Serial.println(ball_position);
    // Serial.println(rounded_pos);
    // Serial.println("---");
}

void Pong::button_1_pressed() {
    bottom_was_pressed = true;
    bottom_is_pressed = true;
    // int rounded_pos = round(ball_position);
    // Serial.print(bottom_zone_min);
    // Serial.print(", ");
    // Serial.println(bottom_zone_max);
    // Serial.println(ball_position);
    // Serial.println(rounded_pos);
    // Serial.println("---");
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
    current_millis = 0;
    last_fade = 0;
    ball_speed = 0;
    ball_position = float(constants::GRID_HEIGHT)/2.0;
    ball_blink_state = true;

    top_zone_min = 0;
    top_zone_max = 0;
    bottom_zone_min = 0;
    bottom_zone_max = 0;

    top_countdown_min = 0;
    top_countdown_max = 0;
    bottom_countdown_min = 0;
    bottom_countdown_max = 0;

    top_half_max_row = 0;
    bottom_half_min_row = 0;

    countdown_begin = 0;
    win_begin = 0;
    both_pressed_begin = 0;

    game_mode = WAIT_TO_START;
    both_pressed = false;
    top_was_pressed = false;
    top_is_pressed = false;
    bottom_was_pressed = false;
    bottom_is_pressed = false;
}

float Pong::map_pot_to_unit(int value) {
    return float(value)/1023.0;
}

void Pong::set_top_zone_size(float percentage) {
    float conformed_percentage = (ZONE_PERCENT_MIN * (1.0 - percentage)) + (ZONE_PERCENT_MAX * percentage);
    float zone_width = (float(constants::GRID_HEIGHT) * 0.5) * conformed_percentage;
    top_zone_min = 0;
    top_zone_max = round(zone_width);
}

void Pong::set_bottom_zone_size(float percentage) {
    float conformed_percentage = (ZONE_PERCENT_MIN * (1.0 - percentage)) + (ZONE_PERCENT_MAX * percentage);
    float zone_width = (float(constants::GRID_HEIGHT) * 0.5) * conformed_percentage;
    bottom_zone_min = constants::GRID_HEIGHT - 1 - round(zone_width);
    bottom_zone_max = constants::GRID_HEIGHT - 1; 
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
    // Could be some float/int division bugs in here...
    int countdown_progress = current_millis - countdown_begin;
    if (countdown_progress <= COUNTDOWN_DURATION / 2) {
        // Start of wipe, filling from ends to middle
        float top_wipe_progress = float(countdown_progress) / float(COUNTDOWN_DURATION / 2);
        top_countdown_min = 0;
        top_countdown_max = int(top_half_max_row * top_wipe_progress);
        if (top_countdown_max > top_half_max_row) {
            top_countdown_max = top_half_max_row;
        }

        float bottom_wipe_progress = 1.0 - top_wipe_progress;
        bottom_countdown_min = int((float(bottom_half_min_row) * (1.0 - bottom_wipe_progress)) + (float(constants::GRID_HEIGHT) * bottom_wipe_progress));
        if (bottom_countdown_min > (constants::GRID_HEIGHT - 1)) {
            bottom_countdown_min = constants::GRID_HEIGHT - 1;
        }
        bottom_countdown_max = constants::GRID_HEIGHT - 1;

    } else if ((countdown_progress > COUNTDOWN_DURATION / 2) and (countdown_progress <= COUNTDOWN_DURATION)) {
        // End of wipe, emptying from ends to middle
        float top_wipe_progress = float(countdown_progress - (COUNTDOWN_DURATION / 2)) / float(COUNTDOWN_DURATION / 2);
        top_countdown_min = int((top_half_max_row + 1) * top_wipe_progress);
        if (top_countdown_min > top_half_max_row) {
            top_countdown_min = top_half_max_row;
        }
        top_countdown_max = top_half_max_row;


        float bottom_wipe_progress = 1.0 - top_wipe_progress;
        bottom_countdown_min = bottom_half_min_row;
        bottom_countdown_max = int((float(bottom_half_min_row) * (1.0 - bottom_wipe_progress)) + (float(constants::GRID_HEIGHT) * bottom_wipe_progress));
        if (bottom_countdown_max > (constants::GRID_HEIGHT - 1)) {
            bottom_countdown_max = constants::GRID_HEIGHT - 1;
        }

    } else {
        switch_to_playing();
    }
}

void Pong::update_playing() {
    int rounded_pos = round(ball_position);
    if (rounded_pos < 0) {
        switch_to_bottom_won();
    }

    if (rounded_pos > constants::GRID_HEIGHT - 1) {
        switch_to_top_won();
    }

    // Check if top has returned
    if (ball_speed < 0) {
        if (rounded_pos <= top_zone_max) {
            if (top_was_pressed) {
                return_ball();
            }
        }
    }

    // Check if bottom has returned
    if (ball_speed > 0) {
        if (rounded_pos >= bottom_zone_min) {
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
    Serial.println("returned");
    ball_speed *= -1.0 * RETURN_SPEED_MULTIPLIER;
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
    for(int index = 0; index < constants::NUM_LEDS; index++) {
        leds[index] = CRGB::Black;
    }
    if (ball_blink_state) {
        draw_ball();
    }
    draw_endzones();

    // Draw top wiper
    for (int row = top_countdown_min; row <= top_countdown_max; row++) {
        for (int column = 0; column < constants::GRID_WIDTH; column++) {
            int index = (row * constants::GRID_WIDTH) + column;
            leds[index] = CRGB::White;
        }
    }
    
    // Draw bottom wiper
    for (int row = bottom_countdown_min; row <= bottom_countdown_max; row++) {
        for (int column = 0; column < constants::GRID_WIDTH; column++) {
            int index = (row * constants::GRID_WIDTH) + column;
            leds[index] = CRGB::White;
        }
    }
}

void Pong::draw_playing() {
    if ((current_millis - last_fade) > FADE_INTERVAL) {
        last_fade = current_millis;
        for(int index = 0; index < constants::NUM_LEDS; index++) {
            leds[index].fadeToBlackBy(FADE_AMOUNT);
        }
    }
    draw_endzones();
    draw_ball();
}

void Pong::draw_top_won() {
    for(int index = 0; index < constants::NUM_LEDS; index++) {
        leds[index] = CRGB::Red;
    }
}

void Pong::draw_bottom_won() {
    for(int index = 0; index < constants::NUM_LEDS; index++) {
        leds[index] = CRGB::Green;
    }
}

void Pong::draw_endzones() {
    // Draw top
    for (int row = int(top_zone_min); row <= int(top_zone_max); row++) {
        for (int column = 0; column < constants::GRID_WIDTH; column++) {
            int index = (row * constants::GRID_WIDTH) + column;
            if (top_is_pressed) {
                leds[index] = CRGB::White;
            } else {
                leds[index] = CRGB::Red;
            }
        }
    }

    // Draw bottom
    for (int row = int(bottom_zone_min); row <= int(bottom_zone_max); row++) {
        for (int column = 0; column < constants::GRID_WIDTH; column++) {
            int index = (row * constants::GRID_WIDTH) + column;
            if (bottom_is_pressed) {
                leds[index] = CRGB::White;
            } else {
                leds[index] = CRGB::Green;
            }
        }
    }
}

void Pong::draw_ball() {
    int row = round(ball_position);
    if (row >= constants::GRID_HEIGHT) {
        row = constants::GRID_HEIGHT - 1;
    }
    if (row < 0) {
        row = 0;
    }
    for (int column = 0; column < constants::GRID_WIDTH; column++) {
        int index = (row * constants::GRID_WIDTH) + column;
        leds[index] = CRGB::Blue;
    }
}


void Pong::switch_to_wait_to_start() {
    game_mode = WAIT_TO_START;
    ball_position = constants::GRID_HEIGHT / 2.0;
}

void Pong::switch_to_countdown() {
    game_mode = COUNTDOWN;
    countdown_begin = current_millis;
    top_countdown_min = top_countdown_max = 0;
    bottom_countdown_min = bottom_countdown_max = constants::GRID_HEIGHT - 1;
}

void Pong::switch_to_playing() {
    game_mode = PLAYING;
    float mult = 1.0;
    int random_val = random(0, 2);
    Serial.println(random_val);
    if (random_val) {
        mult = -1.0;
    }
    ball_speed = INITIAL_BALL_SPEED * mult;
}

void Pong::switch_to_top_won() {
    game_mode = TOP_WON;
    win_begin = current_millis;
}

void Pong::switch_to_bottom_won() {
    game_mode = BOTTOM_WON;
    win_begin = current_millis;
}
