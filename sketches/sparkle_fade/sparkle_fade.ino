#include <FastLED.h>
#include <Arduino.h>

#include "cycler.h"
#include "potentiometer.h"

#define NUM_LEDS 64
#define LED_DATA_PIN 2
#define SPAWN_RATE_POT_PIN A0
#define SPAWN_AMOUNT_POT_PIN A1
#define FADE_RATE_POT_PIN A2
#define FADE_AMOUNT_POT_PIN A3

CRGB leds[NUM_LEDS];
Cycler spawn_timer, fade_timer;
Potentiometer spawn_rate_pot(SPAWN_RATE_POT_PIN);
Potentiometer spawn_amount_pot(SPAWN_AMOUNT_POT_PIN);
Potentiometer fade_rate_pot(FADE_RATE_POT_PIN);
Potentiometer fade_amount_pot(FADE_AMOUNT_POT_PIN);

uint8_t num_to_spawn = 1;
uint8_t fade_amount = 1;
uint8_t random_indexes[NUM_LEDS];

void spawn_lights() {
    //leds[0] = CRGB::White;


    // Shuffle indexes array
    for (uint8_t index = 0; index < NUM_LEDS; index++) {
        uint8_t shuffle_index = random(NUM_LEDS);
        uint8_t temp = random_indexes[index];
        random_indexes[index] = random_indexes[shuffle_index];
        random_indexes[shuffle_index] = temp;
    }

    uint8_t num_spawned = 0;
    for(int index = 0; index < NUM_LEDS; index++) {
        if (num_spawned < num_to_spawn) {
            if (!leds[random_indexes[index]]) {
                leds[random_indexes[index]] = CRGB::White;
                num_spawned++;
            }
        } else {
            break;
        }
    }
    //Serial.println(millis());
}

void fade_lights() {
    for(int index = 0; index < NUM_LEDS; index++) {
        leds[index].fadeToBlackBy(fade_amount);
    }
}

// void set_spawn_rate(uint16_t pot_val) {
//     uint16_t spawn_rate = map(pot_val, 0, 1023, 5, 1000);
//     spawn_timer.set_period_immediate(spawn_rate, true);
// }

// void set_spawn_amount(uint16_t pot_val) {
//     num_to_spawn = map(pot_val, 0, 1023, 0, 10);
// }

// void set_fade_rate(uint16_t pot_val) {
//     uint16_t fade_rate = map(pot_val, 0, 1023, 5, 1000);
//     fade_timer.set_period_immediate(fade_rate, true);
// }

// void set_fade_amount(uint16_t pot_val) {
//     fade_amount = map(pot_val, 0, 1023, 0, 255);
// }

void set_spawn_rate(uint16_t pot_val) {
    uint16_t spawn_rate = map(pot_val, 0, 1023, 5, 1000);
    spawn_timer.set_period_immediate(spawn_rate);
    Serial.print("Spawning every: ");
    Serial.print(spawn_rate);
    Serial.println("ms.");
}

void set_spawn_amount(uint16_t pot_val) {
    num_to_spawn = map(pot_val, 0, 1023, 0, 10);
    Serial.print("Spawning ");
    Serial.print(num_to_spawn);
    Serial.println(" lights per spawn event.");
}

void set_fade_rate(uint16_t pot_val) {
    uint16_t fade_rate = map(pot_val, 0, 1023, 5, 1000);
    fade_timer.set_period_immediate(fade_rate);
    Serial.print("Fading every: ");
    Serial.print(fade_rate);
    Serial.println("ms.");
}

void set_fade_amount(uint16_t pot_val) {
    fade_amount = map(pot_val, 0, 1023, 0, 255);
    Serial.print("Fading ");
    Serial.print(float(fade_amount)/255.0);
    Serial.println(" percent per fade event.");
}


void setup() {
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);
    spawn_timer.init();
    spawn_timer.set_cycle_mode(Cycler::SQUARE);
    spawn_timer.set_period_immediate(200);

    fade_timer.init();
    fade_timer.set_cycle_mode(Cycler::SQUARE);
    fade_timer.set_period_immediate(10);

    spawn_rate_pot.init();
    spawn_amount_pot.init();
    fade_rate_pot.init();
    fade_amount_pot.init();

    for(int index = 0; index < NUM_LEDS; index++) {
        random_indexes[index] = index;
    }

    set_spawn_rate(spawn_rate_pot.get_value());
    set_spawn_amount(spawn_amount_pot.get_value());
    set_fade_rate(fade_rate_pot.get_value());
    set_fade_amount(fade_amount_pot.get_value());
}

void loop() {
    spawn_timer.update(NULL, &spawn_lights);
    fade_timer.update(NULL, &fade_lights);

    spawn_rate_pot.update(&set_spawn_rate);
    spawn_amount_pot.update(&set_spawn_amount);
    fade_rate_pot.update(&set_fade_rate);
    fade_amount_pot.update(&set_fade_amount);

    //Serial.println(spawn_timer.get_value());

    FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
    FastLED.show();
}