// Convenience class to find a tempo by tapping a button

// To use a button, have it ground the pin it's connected to when pressed.

#include "taptempo.h"

TapTempo::TapTempo() {
    for (uint8_t index = 0; index < NUM_TAPS; ++index ) {
        _tap_times[index] = index * 1000;
    }
    _newest_tap_index = 4;
}

void TapTempo::tap() {
    _newest_tap_index = (_newest_tap_index + 1) % NUM_TAPS;
    _tap_times[_newest_tap_index] = millis();
}

uint16_t TapTempo::get_period() {
    uint8_t oldest_tap_index = (_newest_tap_index + 1) % NUM_TAPS;
    uint16_t tap_span = _tap_times[_newest_tap_index] - _tap_times[oldest_tap_index];
    uint16_t average_tap_gap = tap_span / (NUM_TAPS - 1);
    return average_tap_gap;
}

uint16_t TapTempo::get_offset() {
    uint16_t offset = millis() % get_period();
    return offset;
}