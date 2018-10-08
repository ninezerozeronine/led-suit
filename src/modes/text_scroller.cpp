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
    display_pixel_width = 16;
}

void TextScroller::initialise() {
    // for (int offset = 0; offset < 8; offset++) {
    //     byte char_row_byte = pgm_read_byte_near(constants::ASCII_CHARS + 16 + offset);
    //     for (int column = 0; column < 8; column++) {
    //         if (char_row_byte >> (7 - column) & 1 == 1) {
    //             Serial.print("1");
    //         }
    //         else {
    //             Serial.print("0");
    //         }
    //     }
    //     Serial.print(" ");
    //     Serial.println(char_row_byte);
    // }

    for (int index = 0; index < constants::NUM_LEDS; index++) {
            leds[index] = CRGB::Black;
        }
    last_update = millis();
    message_index = constants::NUM_MESSAGES - 1;
    // Serial.println(message_index);
    set_next_message();


}

void TextScroller::initialise_pot_0(int pot_value) {
    set_speed(map_to_speed(pot_value));
}

void TextScroller::set_next_message() {
    // Get the next message index
    message_index = (message_index + 1) % constants::NUM_MESSAGES;
    Serial.println(message_index);

    // Read from progmem into buffer
    Serial.println("before 0");
    strcpy_P(message, (char*)pgm_read_word(&(constants::MESSAGES[message_index])));
    Serial.println("after 0");

    Serial.println(message[0]);
    Serial.println(message[1]);
    Serial.println(message[2]);

    // Count number of characters in message
    Serial.println("before 1");
    num_message_chars = strlen(message);
    Serial.println("after 1");
    Serial.println(num_message_chars);

    // Count number of columns in message
    num_message_columns = num_message_chars * constants::CHAR_WIDTH;
    Serial.println(num_message_columns);
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
        // Serial.print("char_col:");
        // Serial.print(character_column);
        // Serial.print(" ");
        int character_ascii_code = int(message[message_char_index]);
        // Serial.print("msg_char_index:");
        // Serial.print(message_char_index);
        // Serial.print(" ");
        // Serial.print("msg_letter:");
        // Serial.print(message[message_char_index]);
        // Serial.print(" ");
        int character_table_index = map_ascii_to_character_table(character_ascii_code);
        // Serial.print("char_table_index:");
        // Serial.print(character_table_index);
        // Serial.print(" ");

        for (int display_row_index = 0; display_row_index < constants::CHAR_HEIGHT; display_row_index++) {
            int letter_byte_index = (character_table_index * 8) + display_row_index;
            byte char_row_byte = pgm_read_byte_near(constants::ASCII_CHARS + letter_byte_index);
            int led_grid_index = display_pos_to_led_grid_index(display_row_index, display_column_index);
            int led_index = pgm_read_word_near(constants::LED_GRID_INDECIES + led_grid_index);
            if (led_index >= 0) {
                if (char_row_byte >> character_column & 1 == 1) {
                    leds[led_index] = CRGB::Red;
                } else {
                    leds[led_index] = CRGB::Black;
                } 
            }

            if (display_row_index == 0) {
                // Serial.print("letter_byte_index:");
                // Serial.print(letter_byte_index);
                // Serial.print(" ");
                // Serial.print("char_row_byte:");
                // Serial.print(char_row_byte);
                // Serial.print(" ");
                // Serial.println(led_grid_index);
            }
        }
    }
    // Serial.println("---");
}

int TextScroller::display_pos_to_led_grid_index(int display_row_index, int display_column_index) {
    int grid_row_index = top_left_pixel_row + display_row_index;
    int grid_column_index = top_left_pixel_column + display_column_index;
    return (grid_row_index * constants::GRID_WIDTH) + grid_column_index;
}

int TextScroller::map_ascii_to_character_table(int ascii_value) {
    return ascii_value - 32;
}

void TextScroller::set_speed(float speed_) {
    speed = speed_;
}

void TextScroller::process_new_pot_0_value(int pot_value) {
    set_speed(map_to_speed(pot_value));
}

float TextScroller::map_to_speed(int pot_value) {
    return (float(pot_value) / float(1023)) * 0.04;
}