// Class to handle values that cycle over time

#ifndef cycler_h
#define cycler_h

#include <FastLED.h>
#include <Arduino.h>

class Cycler {
    public:
        // The different modes of the cycler:
        // Static doesn't change over time
        // SIN is a sin wave with highest and lowest values of min and max
        // TRIANGLE is a wave that is min at the start and end of the period and
        //          max at a point duty*period through the period and
        //          linearly interpolates in between.
        // SQUARE has a value of max from the start of the period up until duty*period
        //        where it then goes straigt to min.
        enum mode_t {
            STATIC,
            SIN,
            TRIANGLE,
            SQUARE
        };

        Cycler(
            uint16_t period=1000,
            float min=0.0,
            float max=255.0,
            mode_t cycle_mode=STATIC,
            float duty=0.5
        );
        void init();
        void set_cycle_mode(mode_t cycle_mode);
        float get_value();
        void update(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void set_min(float min);
        void set_max(float max);
        void set_duty(float duty);
        void set_period(uint16_t period, bool maintain_progress=false);
        void start_period_now();
        void set_offset(uint16_t offset);

    private:
        // How long it takes to get to the same point in the cycle in milliseconds
        uint16_t _period;

        // The offset from 0 for when the period starts
        uint16_t _milli_offset;

        // The last updates progress through the period normalised between 0 and 1
        float _last_normalised_progress;

        // The max value of the cycler
        float _max;

        // The min value of the cycler
        float _min;

        // The value of the cycler (only used in static mode)
        float _value;

        // The current mode
        mode_t _cycle_mode;

        // When the cycler was last updated
        unsigned long _last_update_time;

        // The duty or ratio of on to off when in SQUARE or TRIANGLE scycle mode
        float _duty;

        // Whetehr the callbacks have been invalidated by changing duty or period
        bool _callbacks_invalidated;

        // Calucualte the current normalised progress
        float _calculate_normalised_progress();

        // Update various modes
        void _update_SIN(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void _update_TRIANGLE(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void _update_SQUARE(void (*min_callback)()=NULL, void (*max_callback)()=NULL);

        // Setup when entering different cycle modes
        float _calculate_STATIC();
        float _calculate_SIN();
        float _calculate_TRIANGLE();
        float _calculate_SQUARE();
};

#endif