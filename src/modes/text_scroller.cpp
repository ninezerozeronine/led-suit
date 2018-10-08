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
    current_message_index = 0;
}

void TextScroller::initialise() {
    last_update = millis();
}

void TextScroller::initialise_pot_0(int pot_value) {
    set_speed(map_to_speed(pot_value));
}

void TextScroller::update() {

}

void TextScroller::apply_to_leds() {
    int num_message_columns = num_message_chars * char_width;
    for (int display_column_index = 0; display_column_index < display_pixel_width; display_column_index++) {
        int message_column_index = (display_column_index + int(message_progress)) % num_message_columns;
        int message_char_index = message_column_index / char_width;
        int character_column = message_column_index % char_width;

    }
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