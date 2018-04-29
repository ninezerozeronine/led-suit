// Class to handle values that cycle over time

#ifndef cycler_h
#define cycler_h

#include <FastLED.h>
#include <Arduino.h>

#define GRADUAL_AMOUNT 10
#define GRADUAL_INTERVAL 10

class Cycler {
    public:
        // The different modes of the cycler:
        // Static doesn't change over time
        // TRIG is a trigonometric (e.g. sin/cos) wave with highest and lowest values
        //      of min and max. Minimums occur at the start and end of the period, 
        //      maximums occur half way through.
        // TRIANGLE is a wave that is min at the start and end of the period and
        //          max at a point duty*period through the period and
        //          linearly interpolates in between.
        // SQUARE has a value of max from the start of the period up until duty*period
        //        where it then goes straigt to min.
        enum mode_t {
            STATIC,
            TRIG,
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
        void update(unsigned long current_time, void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void set_min(float min);
        void set_max(float max);
        void set_duty(float duty);

        void set_period_immediate(uint16_t period, bool maintain_progress=false);
        void set_period_gradual(uint16_t period, uint16_t duration=2000);
        uint16_t get_period();

        void set_offset_immediate(uint16_t offset);
        void set_offset_gradual(uint16_t offset, uint16_t duration=2000);
        uint16_t get_offset();

        // Calucualte the current normalised progress
        float _calculate_normalised_progress();

    private:
        enum gradual_task_t {
            OFFSET,
            PERIOD,
            SKIP
        };

        // How long it takes to get to the same point in the cycle in milliseconds
        uint16_t _period;

        // The target period to migrate to
        uint16_t _target_period;

        // The offset from 0 for when the period starts
        uint16_t _offset;

        // The target offset to migrate to
        uint16_t _target_offset;

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

        unsigned long _current_time;

        // When the cycler last made a gradual change
        unsigned long _last_gradual_time;

        gradual_task_t _gradual_task;

        unsigned long _gradual_deadline;

        // The duty or ratio of on to off when in SQUARE or TRIANGLE scycle mode
        float _duty;

        // Whetehr the callbacks have been invalidated by changing duty or period
        bool _callbacks_invalidated;



        // Update various modes
        void _update_TRIG(float current_normalised_progress, void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void _update_TRIANGLE(float current_normalised_progress, void (*min_callback)()=NULL, void (*max_callback)()=NULL);
        void _update_SQUARE(float current_normalised_progress, void (*min_callback)()=NULL, void (*max_callback)()=NULL);

        // Setup when entering different cycle modes
        float _calculate_STATIC();
        float _calculate_TRIG();
        float _calculate_TRIANGLE();
        float _calculate_SQUARE();

        void _update_graduals();
        void _set_period(uint16_t period, bool maintain_progress=false, bool gradual_offset=false);
        uint16_t _get_gradual_value(uint16_t current, uint16_t target, bool allow_wrap=false);
        int _get_gradual_amount(int time_since_last_grad, int distance);
        int _get_shortest_signed_offset_distance();
};

#endif