// Convenience class to find a tempo by callin a function and the time of a tap.

#include "taptempo.h"

TapTempo::TapTempo() {
    for (uint8_t index = 0; index < NUM_TAPS; ++index ) {
        _tap_times[index] = index * 10;
    }
    _newest_tap_index = NUM_TAPS - 1;
    _period = 10;
    _offset = 0;
}

bool TapTempo::tap() {
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
    unsigned long tap_span = _tap_times[_newest_tap_index] - _tap_times[oldest_tap_index];
    unsigned long average_tap_gap = tap_span / (NUM_TAPS - 1);

    bool all_near_average = true;
    for (uint8_t index = 0; index < NUM_TAPS - 1; ++index ) {
        if (all_near_average) {
            int current_index = _newest_tap_index - index;
            if (current_index < 0) {
                current_index += NUM_TAPS;
            }
            int prev_index = _newest_tap_index - index -1;
            if (prev_index < 0) {
                prev_index += NUM_TAPS;
            }
            long current_gap = _tap_times[current_index] - _tap_times[prev_index];
            long diff = average_tap_gap - current_gap;
            long diff_to_avg = abs(diff);
            float difference = float(diff_to_avg) / float(average_tap_gap);

            // Serial.println("---");
            // Serial.print("Current index: ");
            // Serial.println(current_index);
            // Serial.print("Prev index: ");
            // Serial.println(prev_index);
            // Serial.print("Current tap: ");
            // Serial.println(_tap_times[current_index]);
            // Serial.print("Prev tap: ");
            // Serial.println(_tap_times[prev_index]);
            // Serial.print("Gap: ");
            // Serial.println(current_gap);
            // Serial.print("Diff to avg: ");
            // Serial.println(diff_to_avg);
            // Serial.print("difference: ");
            // Serial.println(difference);

            if (difference > 0.2) {
                all_near_average = false;
            }
        } else {
            break;
        }
    }

    if (all_near_average) {
        // Serial.println("Success!");
        _period = average_tap_gap;
        _offset = _period - (current_millis % _period);
    }
    return all_near_average;
}

uint16_t TapTempo::get_period() {
    return _period;
}

uint16_t TapTempo::get_offset() {
    return _offset;
}