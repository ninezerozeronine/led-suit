#include <FastLED.h>
#include <Arduino.h>

#include "cycler.h"

#define NUM_LEDS 16
#define LED_DATA_PIN 2

CRGB leds[NUM_LEDS];
Cycler cyclers[NUM_LEDS];
uint8_t random_indexes[NUM_LEDS];
Cycler sync_timer;

int current_cycler = 0;
bool sync = true;
bool hold = true;

void randomise_pulsers() {
    for (uint8_t index = 0; index < NUM_LEDS; index++) {
        // int period = random(500, 2000);
        // cyclers[index].set_period_gradual(period);
        // cyclers[index].set_offset_gradual(random(0, period));
        cyclers[index].set_offset_gradual(random(0, 2000));
    }
}

void synchronise_pulsers() {
    for (uint8_t index = 0; index < NUM_LEDS; index++) {
        //cyclers[index].set_period_gradual(2000);
        cyclers[index].set_offset_gradual(0);
    }
}

void shuffle_indexes(){
    for (uint8_t index = 0; index < NUM_LEDS; index++) {
        uint8_t shuffle_index = random(NUM_LEDS);
        uint8_t temp = random_indexes[index];
        random_indexes[index] = random_indexes[shuffle_index];
        random_indexes[shuffle_index] = temp;
    }
}

void next_step() {
    if (hold) {
        current_cycler++;
        if (current_cycler >= NUM_LEDS) {
            hold = false;
            sync = !sync;
            current_cycler = 0;
            shuffle_indexes();
        }
    } else {
        if (sync) {
            cyclers[random_indexes[current_cycler]].set_period_gradual(2000);
            cyclers[random_indexes[current_cycler]].set_offset_gradual(0);
        } else {
            int period = random(500, 2000);
            cyclers[random_indexes[current_cycler]].set_period_gradual(period);
            cyclers[random_indexes[current_cycler]].set_offset_gradual(random(0, period));
        }
        current_cycler++;
        if (current_cycler >= NUM_LEDS) {
            hold = true;
            current_cycler = 0;
        }
    }
}


void setup() {
    // put your setup code here, to run once:
    FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);
    sync_timer.init();
    sync_timer.set_cycle_mode(Cycler::SQUARE);
    sync_timer.set_period_immediate(15000/NUM_LEDS);
    for (uint8_t index = 0; index < NUM_LEDS; index++) {
        cyclers[index].init();
        cyclers[index].set_cycle_mode(Cycler::TRIANGLE);
        cyclers[index].set_period_immediate(2000);
    }

    for(int index = 0; index < NUM_LEDS; index++) {
        random_indexes[index] = index;
    }
    shuffle_indexes();
    // Serial.begin(9600);
}

void loop() {
    // sync_timer.update(&randomise_pulsers, &synchronise_pulsers);
    sync_timer.update(&next_step);
    for (uint8_t index = 0; index < NUM_LEDS; index++) {
        cyclers[index].update();
        int value = dim8_raw(int(cyclers[index].get_value()));
        leds[index].setHSV(0, 0, value);
    }
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.setBrightness(64);
    FastLED.show();
    // Serial.println(current_cycler);
}