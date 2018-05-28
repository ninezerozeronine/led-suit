#include "mode.h"

Mode::Mode() {
    constructor_defaults();
}


Mode::Mode(CRGB* leds_) {
    constructor_defaults();
    leds = leds_;
}


void Mode::constructor_defaults() {
    leds = NULL;
}