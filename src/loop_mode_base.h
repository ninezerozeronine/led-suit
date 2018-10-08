#ifndef LOOP_MODE_BASE_H
#define LOOP_MODE_BASE_H

#define NUM_LOOP_MODES 4

#include <Arduino.h>
#include "mode_base.h"
#include "constants.h"
#include "unit_offset.h"

class LoopModeBase: public Mode {
    public:
        LoopModeBase();
        LoopModeBase(CRGB* leds_);
        virtual void update();
        virtual void initialise();
        virtual void apply_to_leds();
        virtual void initialise_pot_0(int value);
        virtual void initialise_pot_1(int value);
        virtual void process_new_pot_0_value(int value);
        virtual void process_new_pot_1_value(int value);
        virtual void button_0_pressed();
        virtual void set_speed(float speed);
        virtual void set_pattern_width(int pattern_width_);

    protected:
        virtual CHSV pattern_colour_lookup(float position) = 0;

    private:
        void constructor_defaults();
        void apply_to_leds_vert();
        void apply_to_leds_vert_split();
        void apply_to_leds_horiz();
        void apply_to_leds_horiz_split();
        float map_pot_0_value(int value);
        int map_pot_1_value(int value);
        int output_to_pattern(int output);
        float pattern_to_unit(int position);
        void set_next_mode();

        UnitOffset unit_offset;
        int pattern_width;
        float base_speed;
        byte current_mode;
};

#endif