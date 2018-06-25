// Convenience class to see how fast the loop function is

#include "loopTimer.h"

LoopTimer::LoopTimer() {
    constructor_defaults();
}


LoopTimer::LoopTimer(int _loops_to_count) {
    constructor_defaults();
    loops_to_count = _loops_to_count;
}


void LoopTimer::constructor_defaults() {
    loops_to_count = 20;
    num_loops = 0;
    last_count_millis = 0;
    loop_time = 0;
}


void LoopTimer::update() {
    // If we've counted enough loops
    if (num_loops >= loops_to_count) {
        // Get current and elasped millis
        unsigned int current_millis = millis();
        unsigned int elapsed_millis = current_millis - last_count_millis;

        // Calculate loop time
        loop_time = float(elapsed_millis) / float(loops_to_count);

        // Reset counters
        num_loops = 0;
        last_count_millis = current_millis;
    // Else we haven't counted enought loops yet
    } else {
        num_loops++;
    }
}


float LoopTimer::get_loop_time() {
    return loop_time;
}