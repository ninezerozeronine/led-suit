#include <FastLED.h>
#include <Arduino.h>

#include "button.h"
#include "cycler.h"
#include "taptempo.h"

#define NUM_LEDS 64
#define DATA_PIN 2
#define BUTTON_PIN 3

CRGB leds[NUM_LEDS];
Cycler cycler;
TapTempo taptempo;
Button button(BUTTON_PIN);

void button_pressed() {
    if (taptempo.tap()) {
        cycler.set_period_gradual(taptempo.get_period() * 2.0);
        cycler.set_offset_gradual(taptempo.get_offset());
    }
}

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    button.init();
    cycler.init();
    cycler.set_min(0);
    cycler.set_max(63.9);
    cycler.set_cycle_mode(Cycler::TRIANGLE);
}

void loop() {
    button.update(&button_pressed);
    cycler.update();
    for(int index = 0; index < NUM_LEDS; index++) {
        if (index <= int(cycler.get_value())) {
            leds[index] = CRGB::Orange;
        } else {
            leds[index] = CRGB::Black;
        }
    }
    FastLED.setBrightness(dim8_raw(128));
    FastLED.show();
}