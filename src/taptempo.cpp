// Convenience class to find a tempo by callin a function and the time of a tap.

#include "taptempo.h"

TapTempo::TapTempo() {
    for (uint8_t index = 0; index < NUM_TAPS; ++index ) {
        _tap_times[index] = index * 1000;
    }
    _newest_tap_index = 4;
    _period = 1000;
    _offset = 0;
}

void TapTempo::tap() {
    unsigned long current_millis = millis();

    _newest_tap_index = (_newest_tap_index + 1) % NUM_TAPS;
    _tap_times[_newest_tap_index] = current_millis;

    // Serial.print("[");
    // for (uint8_t index = 0; index < NUM_TAPS; ++index ) {
    //     Serial.print(_tap_times[index]);
    //     Serial.print(" ");
    // }
    // Serial.println("]");

    uint8_t oldest_tap_index = (_newest_tap_index + 1) % NUM_TAPS;
    uint16_t tap_span = _tap_times[_newest_tap_index] - _tap_times[oldest_tap_index];
    uint16_t average_tap_gap = tap_span / (NUM_TAPS - 1);
    _period = average_tap_gap;

    _offset = _period - (current_millis % _period);
}

uint16_t TapTempo::get_period() {
    return _period;
}

uint16_t TapTempo::get_offset() {
    return _offset;
}