#ifndef TEXTSCROLLER_H
#define TEXTSCROLLER_H

#include <avr/pgmspace.h>
#include <Arduino.h>
#include "mode_base.h"
#include "constants.h"

class TextScroller: public Mode {
    public:
        TextScroller();
        TextScroller(CRGB* leds_);
        void apply_to_leds();
        void initialise();
        void update();
        void initialise_pot_0(int pot_value);
        void process_new_pot_0_value(int pot_value);
        
    private:
        void constructor_defaults();
        float map_to_speed(int pot_value);
        void update_message_progress();
        void set_next_message();
        int map_ascii_to_character_table(int ascii_value);
        int display_pos_to_led_grid_index(int display_row_index, int display_column_index);
        void set_speed(float speed_);

        unsigned long last_update;
        float speed;
        float message_progress;
        int message_index;
        int num_message_chars;
        int num_message_columns;
        int top_left_pixel_row;
        int top_left_pixel_column;
        int display_pixel_width;
        char message[64];
};

#endif