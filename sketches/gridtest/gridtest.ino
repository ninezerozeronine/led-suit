#include <FastLED.h>
#include <Arduino.h>

#define NUM_LEDS 150
#define DATA_PIN 2

CRGB leds[NUM_LEDS];
unsigned long last_millis = 0;
uint16_t last_index = 0;
uint8_t brightness = 0;
uint8_t hue = 0;
uint8_t saturation = 0;
uint16_t num_lit = 0;

void RGB_worm(){
    for(int index = 0; index < NUM_LEDS; index++) {
        leds[index] = CRGB::Red;
        leds[(index + 1) % (NUM_LEDS )] = CRGB::Green;
        leds[(index + 2) % (NUM_LEDS)] = CRGB::Blue;
        FastLED.show();
        // clear this led for the next time around the loop
        leds[index] = CRGB::Black;
        leds[(index + 1) % (NUM_LEDS)] = CRGB::Black;
        leds[(index + 2) % (NUM_LEDS)] = CRGB::Black;
        delay(200);
    }
}

void random_red() {
    uint16_t new_index = random(0,NUM_LEDS);
    leds[last_index] = CRGB::Black;
    leds[new_index] = CRGB::Red;
    last_index = new_index;
    FastLED.show();
}

void num_and_brightness_white(){
    unsigned long current_millis = millis();
    if (last_millis - current_millis > 10) {
        uint16_t num_pot = analogRead(A0);
        uint16_t brightness_pot = analogRead(A1);
        uint16_t hue_pot = analogRead(A2);
        uint16_t saturation_pot = analogRead(A3);

        num_lit = map(num_pot, 0, 1023, 0, NUM_LEDS);
        brightness = map(brightness_pot, 0, 1023, 0, 255);

        Serial.print(num_lit);
        Serial.print(",");
        Serial.println(brightness);
    }

    for(int index = 0; index < NUM_LEDS; index++) {
        if (index + 1 <= num_lit) {
            leds[index] = CRGB::White;
        } else {
            leds[index] = CRGB::Black;
        } 
    }
    FastLED.setBrightness(brightness);
    FastLED.show();
    last_millis = current_millis;
}

void num_and_hsv(){
    unsigned long current_millis = millis();
    if (last_millis - current_millis > 10) {
        uint16_t num_pot = analogRead(A0);
        uint16_t hue_pot = analogRead(A1);
        uint16_t saturation_pot = analogRead(A2);
        uint16_t brightness_pot = analogRead(A3);

        num_lit = map(num_pot, 0, 1023, 0, NUM_LEDS);
        brightness = map(brightness_pot, 0, 1023, 0, 255);
        hue = map(hue_pot, 0, 1023, 0, 255);
        saturation = map(saturation_pot, 0, 1023, 0, 255);

        // Serial.print(num_lit);
        // Serial.print(",");
        // Serial.print(brightness);
        // Serial.print(",");
        // Serial.print(hue);
        // Serial.print(",");
        // Serial.println(saturation);
    }

    for(int index = 0; index < NUM_LEDS; index++) {
        if (index + 1 <= num_lit) {
            leds[index].setHSV(hue, saturation, 255);
        } else {
            leds[index] = CRGB::Black;
        } 
    }
    FastLED.setBrightness(dim8_raw(brightness));
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
    FastLED.show();
    last_millis = current_millis;
}

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
    // RGB_worm();
    // random_red();
    // num_and_brightness_white();
    num_and_hsv();
}