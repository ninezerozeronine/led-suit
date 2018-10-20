#include "text_scroller.h"

TextScroller::TextScroller() : Mode() {
    constructor_defaults();
}

TextScroller::TextScroller(CRGB* leds_) : Mode(leds_) {
    constructor_defaults();
}

void TextScroller::constructor_defaults() {
    last_update = 0;
    speed = 0.01;
    message_index = 0;
    num_message_chars = 0;
    num_message_columns = 0;
    top_left_pixel_row = 0;
    top_left_pixel_column = 0;
    display_pixel_width = 8;
    text_hue = 0;
    bg_hue = 0;
    bg_val = 0;
    orientation = HORIZONTAL;
}

void TextScroller::initialise() {
    for (int index = 0; index < constants::NUM_LEDS; index++) {
            leds[index] = CRGB::Black;
        }
    last_update = millis();
    message_index = constants::NUM_MESSAGES - 1;
    set_next_message();
    orientation = VERTICAL;
    swap_orientation();
}

void TextScroller::initialise_pot_0(int pot_value) {
    set_speed(map_to_speed(pot_value));
}

void TextScroller::initialise_pot_1(int pot_value) {
    set_text_hue(map_to_byte(pot_value));
}

void TextScroller::initialise_pot_2(int pot_value) {
    set_bg_hue(map_to_byte(pot_value));
}

void TextScroller::initialise_pot_3(int pot_value) {
    set_bg_val(map_to_byte(pot_value));
}

void TextScroller::set_next_message() {
    // Get the next message index
    message_index = (message_index + 1) % constants::NUM_MESSAGES;

    // Read from progmem into buffer
    strcpy_P(message, (char*)pgm_read_word(&(constants::MESSAGES[message_index])));

    // Count number of characters in message
    num_message_chars = strlen(message);

    // Count number of columns in message
    num_message_columns = num_message_chars * constants::CHAR_WIDTH;

    // Reset message progress
    message_progress = 0;
}

void TextScroller::update() {
    unsigned long current_millis = millis();
    unsigned long elapsed_millis = current_millis - last_update;
    message_progress += float(elapsed_millis) * speed;
    if (message_progress > float(num_message_columns)) {
        message_progress = message_progress - num_message_columns;
    }
    last_update = current_millis;
}

void TextScroller::apply_to_leds() {
    for (int display_column_index = 0; display_column_index < display_pixel_width; display_column_index++) {
        // The column of the message we want to display (repeating the message over the length of the display)
        int message_column_index = (display_column_index + int(message_progress)) % num_message_columns;

        // The character in the message the column is in
        int message_char_index = message_column_index / constants::CHAR_WIDTH;

        // The column in the character being displayed
        int character_column = message_column_index % constants::CHAR_WIDTH;

        int character_ascii_code = int(message[message_char_index]);

        int character_table_index = map_ascii_to_character_table(character_ascii_code);

        for (int display_row_index = 0; display_row_index < constants::CHAR_HEIGHT; display_row_index++) {
            // Index of the byte in the character map table we want to read for the row of the character we're displaying
            int letter_byte_index = (character_table_index * constants::CHAR_WIDTH) + display_row_index;

            // Get the byte for the row we want to draw
            byte char_row_byte = pgm_read_byte_near(constants::ASCII_CHARS + letter_byte_index);

            // Covert from coords on the diplay grid to an index on the main led grid
            int led_grid_index = display_pos_to_led_grid_index(display_row_index, display_column_index);

            // The the index of the LED we'll be drawing to
            int led_index = pgm_read_word_near(constants::LED_GRID_INDECIES + led_grid_index);

            // If the LED on the grid is in a position that has a physical LED
            if (led_index >= 0) {
                // Check whether the pixel we want to draw is on or off
                if (char_row_byte >> character_column & 1 == 1) {
                    leds[led_index] = CHSV(text_hue, 255, 255);;
                } else {
                    leds[led_index] = CHSV(bg_hue, 255, bg_val);;
                } 
            }
        }
    }
}

int TextScroller::display_pos_to_led_grid_index(int display_row_index, int display_column_index) {
    int grid_row_index = 0;
    int grid_column_index = 0;

    if (orientation == HORIZONTAL) {
        grid_row_index = top_left_pixel_row + display_row_index;
        grid_column_index = top_left_pixel_column + display_column_index;
    } else {
        grid_row_index = top_left_pixel_row + display_column_index;
        grid_column_index = top_left_pixel_column - display_row_index;
    }

    int led_grid_index = (grid_row_index * constants::GRID_WIDTH) + grid_column_index;
    return led_grid_index;
}

int TextScroller::map_ascii_to_character_table(int ascii_value) {
    return ascii_value - 32;
}

void TextScroller::set_speed(float speed_) {
    speed = speed_;
}

void TextScroller::set_text_hue(byte hue) {
    text_hue = hue;
}

void TextScroller::set_bg_hue(byte hue) {
    bg_hue = hue;
}

void TextScroller::set_bg_val(byte val) {
    bg_val = val;
}

void TextScroller::process_new_pot_0_value(int pot_value) {
    set_speed(map_to_speed(pot_value));
}

void TextScroller::process_new_pot_1_value(int pot_value) {
    set_text_hue(map_to_byte(pot_value));
}

void TextScroller::process_new_pot_2_value(int pot_value) {
    set_bg_hue(map_to_byte(pot_value));
}

void TextScroller::process_new_pot_3_value(int pot_value) {
    set_bg_val(map_to_byte(pot_value));
}

float TextScroller::map_to_speed(int pot_value) {
    return (float(pot_value) / float(1023)) * 0.04;
}

byte TextScroller::map_to_byte(int pot_value) {
    return int((float(pot_value) / float(1023)) * 255);
}

void TextScroller::button_0_pressed() {
    set_next_message();
}

void TextScroller::button_1_pressed() {
    swap_orientation();
}

void TextScroller::swap_orientation() {
    if (orientation == HORIZONTAL) {
        orientation = VERTICAL;
        top_left_pixel_row = constants::VERT_TOP_LEFT_ROW;
        top_left_pixel_column = constants::VERT_TOP_LEFT_COLUMN;
        display_pixel_width = constants::VERT_DISPLAY_WIDTH;
    } else {
        orientation = HORIZONTAL;
        top_left_pixel_row = constants::HORIZ_TOP_LEFT_ROW;
        top_left_pixel_column = constants::HORIZ_TOP_LEFT_COLUMN;
        display_pixel_width = constants::HORIZ_DISPLAY_WIDTH;
    }

    for (int index = 0; index < constants::NUM_LEDS; index++) {
            leds[index] = CRGB::Black;
    }
}