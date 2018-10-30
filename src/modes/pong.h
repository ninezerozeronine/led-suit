#ifndef PONG_H
#define PONG_H

#include <Arduino.h>
#include "mode_base.h"
#include "constants.h"

#define ZONE_PERCENT_MIN 0.05
#define ZONE_PERCENT_MAX 0.5
#define FADE_INTERVAL 20
#define FADE_AMOUNT 100
#define INITIAL_BALL_SPEED 0.0025
#define RETURN_SPEED_MULTIPLIER 1.1
#define COUNTDOWN_DURATION 3500

class Pong: public Mode {
    public:
        Pong();
        Pong(CRGB* leds_);
        void initialise();
        void initialise_pot_0(int value);
        void initialise_pot_1(int value);
        void initialise_button_1(byte state);
        void initialise_button_2(byte state);

        void process_new_pot_0_value(int value);
        void process_new_pot_1_value(int value);
        void button_0_pressed();
        void button_1_pressed();
        void button_0_released();
        void button_1_released();
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
        float map_pot_to_unit(int value);

        void set_top_zone_size(float percentage);
        void set_bottom_zone_size(float percentage);

        void update_wait_to_start();
        void update_countdown();
        void update_playing();
        void update_top_won();
        void update_bottom_won();
        void return_ball();

        void draw_wait_to_start();
        void draw_countdown();
        void draw_playing();
        void draw_top_won();
        void draw_bottom_won();
        void draw_endzones();
        void draw_ball();

        void switch_to_wait_to_start();
        void switch_to_countdown();
        void switch_to_playing();
        void switch_to_top_won();
        void switch_to_bottom_won();


        unsigned long last_update;
        unsigned long elapsed_millis;
        unsigned long current_millis;
        unsigned long last_fade;
        float ball_speed;
        float ball_position;
        bool ball_blink_state;
        int top_zone_min;
        int top_zone_max;
        int bottom_zone_min;
        int bottom_zone_max;
        int top_countdown_min;
        int top_countdown_max;
        int bottom_countdown_min;
        int bottom_countdown_max;
        int top_half_max_row;
        int bottom_half_min_row;
        unsigned long countdown_begin;
        unsigned long win_begin;
        unsigned long both_pressed_begin;
        bool both_pressed;

        game_mode_t game_mode;
        bool top_was_pressed;
        bool top_is_pressed;
        bool bottom_was_pressed;
        bool bottom_is_pressed;
};

#endif