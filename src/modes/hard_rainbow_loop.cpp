#include "hard_rainbow_loop.h"

HardRainbowLoop::HardRainbowLoop() : LoopModeBase() {
    constructor_defaults();
}

HardRainbowLoop::HardRainbowLoop(CRGB* leds_) : LoopModeBase(leds_) {
    constructor_defaults();
}

void HardRainbowLoop::constructor_defaults() {
    num_bars = 5;
}

CHSV HardRainbowLoop::pattern_colour_lookup(float position) {
    position = position * num_bars;
    byte hue = 255.0/float(num_bars) * int(position);
    return CHSV(hue, 255, 255);
}

void HardRainbowLoop::set_num_bars(byte num_bars_) {
    num_bars = num_bars_;
}

void HardRainbowLoop::initialise_pot_2(int value) {
    set_num_bars(map_pot_2_value(value));
}

void HardRainbowLoop::process_new_pot_2_value(int value) {
    set_num_bars(map_pot_2_value(value));
}

byte HardRainbowLoop::map_pot_2_value(int value) {
    return map(value, 0, 1023, 1, 10);
}