#include <FastLED.h>
#include <Arduino.h>

#include "constants.h"
#include "linear_fill.h"
#include "potentiometer.h"

CRGB leds[NUM_LEDS];

Potentiometer pot_0(POT_0_PIN);
Potentiometer pot_1(POT_1_PIN);
Potentiometer pot_2(POT_2_PIN);
Potentiometer pot_3(POT_3_PIN);
Potentiometer pot_4(POT_4_PIN);

Mode * current_mode_ptr;

void pot_0_updated(uint16_t new_val){
    current_mode_ptr->pot_0(new_val);
}

void pot_1_updated(uint16_t new_val){
    current_mode_ptr->pot_1(new_val);
}

void pot_2_updated(uint16_t new_val){
    current_mode_ptr->pot_2(new_val);
}

void pot_3_updated(uint16_t new_val){
    current_mode_ptr->pot_3(new_val);
}

void pot_4_updated(uint16_t new_val){
    current_mode_ptr->pot_4(new_val);
}

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);

    pot_0.init();
    pot_1.init();
    pot_2.init();
    pot_3.init();
    pot_4.init();

    delay(50);

    for(int index = 0; index < NUM_LEDS; index++) {
        leds[index] = CRGB::Red;
    }

    current_mode_ptr = new LinearFill(leds);
}

void loop() {
    Serial.println(millis());

    unsigned long current_millis = millis();

    pot_0.update(&pot_0_updated);
    pot_1.update(&pot_1_updated);
    pot_2.update(&pot_2_updated);
    pot_3.update(&pot_3_updated);
    pot_4.update(&pot_4_updated);

    current_mode_ptr->update(current_millis);

    FastLED.setBrightness(128);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
    FastLED.show();
}
