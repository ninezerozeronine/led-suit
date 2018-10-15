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
        void initialise_pot_1(int pot_value);
        void process_new_pot_1_value(int pot_value);
        void initialise_pot_2(int pot_value);
        void process_new_pot_2_value(int pot_value);
        void initialise_pot_3(int pot_value);
        void process_new_pot_3_value(int pot_value);
        void button_0_pressed();
        void button_1_pressed();
        
    private:
        void constructor_defaults();
        float map_to_speed(int pot_value);
        byte map_to_byte(int pot_value);
        void update_message_progress();
        void set_next_message();
        int map_ascii_to_character_table(int ascii_value);
        int display_pos_to_led_grid_index(int display_row_index, int display_column_index);
        void set_speed(float speed_);
        void set_text_hue(byte hue);
        void set_bg_hue(byte hue);
        void set_bg_val(byte val);
        void swap_orientation();

        enum orientation_t {
            HORIZONTAL,
            VERTICAL
        };

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
        byte text_hue;
        byte bg_hue;
        byte bg_val;
        orientation_t orientation;
};

#endif