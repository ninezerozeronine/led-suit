#ifndef PONG_H
#define PONG_H

#include <Arduino.h>
#include "mode_base.h"
#include "constants.h"

#define ZONE_SIZE_MIN 0.1
#define ZONE_SIZE_MAX 0.5

class Pong: public Mode {
    public:
        Pong();
        Pong(CRGB* leds_);
        void initialise();
        void initialise_pot_0(int value);
        void initialise_pot_1(int value);
        void initialise_pot_2(int value);
        void initialise_button_1(byte state);
        void initialise_button_2(byte state);

        void process_new_pot_0_value(int value);
        void process_new_pot_1_value(int value);
        void process_new_pot_2_value(int value);
        void button_1_pressed();
        void button_2_pressed();
        void button_1_released();
        void button_2_released();
        void update();

        void apply_to_leds();

    private:
        enum game_mode_t {
            WAIT_TO_START,
            COUNTDOWN,
            PLAYING,
            TOP_WON,
            BOTTOM_WON
        };

        void constructor_defaults();
        int map_pot_0_value(int value);
        byte map_pot_to_byte(int pot_value);

        void set_zone_size(float percentage);
        void set_top_hue(byte hue);
        void set_bottom_hue(bye_hue);

        void update_wait_to_start();
        void update_countdown();
        void update_playing();
        void update_top_won();
        void update_bottom_won();

        void draw_wait_to_start();
        void draw_countdown();
        void draw_playing();
        void draw_top_won();
        void draw_bottom_won();

        void switch_to_wait_to_start();
        void switch_to_countdown();
        void switch_to_playing();
        void switch_to_top_wins();
        void switch_to_bottom_wins();

        unsigned long last_update;
        float ball_speed;
        float ball_position;
        float zone_size;
        int countdown_time;
        float win_wipe_progress;
        int top_hue;
        int bottom_hue;
        unsigned long both_pressed_begin;

        game_mode_t game_mode;
        bool top_was_pressed;
        bool top_is_pressed;
        bool bottom_was_pressed;
        bool bottom_is_pressed;
};

#endif