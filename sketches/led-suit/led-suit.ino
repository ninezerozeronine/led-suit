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
        leds[index] = CRGB::Black;
    }

    current_mode_ptr = new LinearFill(leds);
}

void loop() {
    current_millis = millis()

    pot0.update(&current_mode_ptr->pot0);
    pot1.update(&current_mode_ptr->pot1);
    pot2.update(&current_mode_ptr->pot2);
    pot3.update(&current_mode_ptr->pot3);
    pot4.update(&current_mode_ptr->pot4);

    current_mode_ptr->update(current_millis);

    FastLED.setBrightness(128);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
    FastLED.show();
}
