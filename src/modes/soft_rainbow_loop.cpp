#include "soft_rainbow_loop.h"

SoftRainbowLoop::SoftRainbowLoop() : LoopModeBase() {

}

SoftRainbowLoop::SoftRainbowLoop(CRGB* leds_) : LoopModeBase(leds_) {

}

CHSV SoftRainbowLoop::pattern_colour_lookup(float position) {
    byte hue = 255 * position;
    return CHSV(hue, 255, 255);
}