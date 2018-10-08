#ifndef TEXTSCROLLER_H
#define TEXTSCROLLER_H

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
        void initialise_pot_1(int pot_value);
        void process_new_pot_0_value(int pot_value);
        void process_new_pot_1_value(int pot_value);
        void button_0_pressed()
    private:
        void constructor_defaults();
        float map_to_speed(int pot_value);
        void update_message_progress();
        void set_next_message();

        unsigned long last_update;
        float speed;
        float message_progress;
        byte top_left_pixel_x;
        byte top_left_pixel_y;
        byte display_pixel_width;
        byte current_message_index;
        byte current_message_length;
        char message[64];
};

#endif