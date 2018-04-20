// Convenience class to find a tempo by tapping a button

#ifndef taptempo_h
#define taptempo_h

#define NUM_TAPS 5

#include "Arduino.h"

class TapTempo {
    public:
        TapTempo();
        void tap();
        uint16_t get_period();
        uint16_t get_offset();

    private:
        // The time of each of the taps
        unsigned long _tap_times[NUM_TAPS];
  
        // The index where the last tap time was stored
        uint8_t _newest_tap_index;
};

#endif