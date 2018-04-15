// Class to handle values that cycle over time

#ifndef cycler_h
#define cycler_h

#include <FastLED.h>
#include <Arduino.h>

class Cycler {
    public:
        enum mode_t {
            STATIC,
            SIN,
            SAWTOOTH,
            TRIANGLE,
            SQUARE
        };
        Cycler(
            unsigned long period=1000,
            float min=0.0,
            float max=255.0,
            mode_t cycle_mode=STATIC
        );
        void init();
        void set_cycle_mode(mode_t cycle_mode);
        float get_value();
        void update(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void set_min(float min);
        void set_max(float max);
        void set_period(unsigned long period);
        void set_min_now();
        void set_max_now();
        void set_progress(unsigned long progress);


    private:
        // How long it takes to get to the same point in the cycle in milliseconds
        unsigned long _period;

        // How far through the period we are in milliseconds
        unsigned long _progress;

        // The current value of the cycler
        float _value;

        // The max value of the cycler
        float _max;

        // The min value of the cycler
        float _min;

        // The current mode
        mode_t _cycle_mode;

        // When the cycler was last updated
        unsigned long _last_update;

        // The duty or ratio of on to off when in SQUARE cycle mode
        float _duty;

        // Update various modes
        void _update_sin(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void _update_sawtooth(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void _update_triangle(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void _update_square(void (*min_callback)()=NULL, void (*max_callback)()=NULL);

        // Setup when entering different cycle modes
        void _setup_SIN_cycle();
        void _setup_SAWTOOTH_cycle();
        void _setup_TRIANGLE_cycle();
        void _setup_SQUARE_cycle();


        // Calculate speed based on period
        void _calculate_speed();
};

#endif