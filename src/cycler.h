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
        void start_period_now();

    private:
        // How long it takes to get to the same point in the cycle in milliseconds
        unsigned long _period;

        // The offset from 0 for when the period starts
        unsigned long _milli_offset;

        // The last updates progress through the period normalised between 0 and 1
        float _last_normalised_progress;

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

        // Calucualte the current normalised progress
        float _calculate_normalised_progress();

        // Update various modes
        void _update_sin(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void _update_sawtooth(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void _update_square(void (*min_callback)()=NULL, void (*max_callback)()=NULL);

        // Setup when entering different cycle modes
        void _calculate_STATIC_();
        void _calculate_SIN();
        void _calculate_TRIANGLE();
        void _calculate_SQUARE();
};

#endif