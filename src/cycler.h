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
            // SAWTOOTH,
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
        void set_period(unsigned long period, bool maintain_progress=false);
        // void set_progress(float progress);
        // void set_progress(unsigned long progress);
        void start_period_now();

    private:
        // How long it takes to get to the same point in the cycle in milliseconds
        unsigned long _period;

        // How far through the period we are in milliseconds
        // unsigned long _milli_progress;

        // The offset from 0 for when the period starts
        unsigned long _milli_offset;

        // The progress through the period normalised between 0 and 1;
        // float _normalised_progress;

        // Progress through the period in millis last update
        unsigned long _last_milli_progress;

        // The last value of the cycler
        // float _last_value;

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

        // Whetehr the callbacks have been invalidated by changing duty or period
        bool _callbacks_invalidated;

        // Reconfigure the cycler when period or duty changes
        // void _reconfigure();

        // Update various modes
        void _update_sin(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void _update_sawtooth(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        // void _update_triangle(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void _update_square(void (*min_callback)()=NULL, void (*max_callback)()=NULL);

        // Setup when entering different cycle modes
        void _set_cycle_mode_STATIC();
        void _set_cycle_mode_SIN();
        //void _set_cycle_mode_SAWTOOTH();
        void _set_cycle_mode_TRIANGLE();
        void _set_cycle_mode_SQUARE();

        // Setup when entering different cycle modes
        // void _init_cycle();
        // void _init_STATIC_cycle();
        // void _init_SIN_cycle();
        // void _init_SAWTOOTH_cycle();
        // void _init_TRIANGLE_cycle();
        // void _init_SQUARE_cycle();

        // Setup when entering different cycle modes
        void _calculate_cycle();
        void _calculate_STATIC_cycle();
        void _calculate_SIN_cycle();
        // void _calculate_SAWTOOTH_cycle();
        void _calculate_TRIANGLE_cycle();
        void _calculate_SQUARE_cycle();

        // Calculate speed based on period
        // void _calculate_speed();
};

#endif