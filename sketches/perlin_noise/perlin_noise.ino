#include <FastLED.h>
#include <Arduino.h>

#include "loopTimer.h"
#include "potentiometer.h"


const int NUM_LEDS = 256;
const int LED_DATA_PIN = 2;
const int RED_POT_PIN = A0;
const int GREEN_POT_PIN = A1;

const byte LED_X_VALS[NUM_LEDS] PROGMEM = {
    0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
    255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,
    0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
    255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,

    0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
    255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,
    0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
    255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,

    0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
    255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,
    0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
    255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,

    0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
    255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0,
    0,   17,  34,  51,     68,  85,  102, 119,    136, 153, 170, 187,    204, 221, 238, 255,
    255, 238, 221, 204,    187, 170, 153, 136,    119, 102, 85,  68,     51,  34,  17,  0
};

const byte LED_Y_VALS[NUM_LEDS] PROGMEM = {
    255, 255, 255, 255,    255, 255, 255, 255,    255, 255, 255, 255,    255, 255, 255, 255,
    238, 238, 238, 238,    238, 238, 238, 238,    238, 238, 238, 238,    238, 238, 238, 238,
    221, 221, 221, 221,    221, 221, 221, 221,    221, 221, 221, 221,    221, 221, 221, 221,
    204, 204, 204, 204,    204, 204, 204, 204,    204, 204, 204, 204,    204, 204, 204, 204,

    187, 187, 187, 187,    187, 187, 187, 187,    187, 187, 187, 187,    187, 187, 187, 187,
    170, 170, 170, 170,    170, 170, 170, 170,    170, 170, 170, 170,    170, 170, 170, 170,
    153, 153, 153, 153,    153, 153, 153, 153,    153, 153, 153, 153,    153, 153, 153, 153,
    136, 136, 136, 136,    136, 136, 136, 136,    136, 136, 136, 136,    136, 136, 136, 136,

    119, 119, 119, 119,    119, 119, 119, 119,    119, 119, 119, 119,    119, 119, 119, 119,
    102, 102, 102, 102,    102, 102, 102, 102,    102, 102, 102, 102,    102, 102, 102, 102,
    85,  85,  85,  85,     85,  85,  85,  85,     85,  85,  85,  85,     85,  85,  85,  85, 
    68,  68,  68,  68,     68,  68,  68,  68,     68,  68,  68,  68,     68,  68,  68,  68, 

    51,  51,  51,  51,     51,  51,  51,  51,     51,  51,  51,  51,     51,  51,  51,  51, 
    34,  34,  34,  34,     34,  34,  34,  34,     34,  34,  34,  34,     34,  34,  34,  34, 
    17,  17,  17,  17,     17,  17,  17,  17,     17,  17,  17,  17,     17,  17,  17,  17, 
    0,   0,   0,   0,      0,   0,   0,   0,      0,   0,   0,   0,      0,   0,   0,   0
};

CRGB leds[NUM_LEDS];
Potentiometer red_pot(RED_POT_PIN);
Potentiometer green_pot(GREEN_POT_PIN);
LoopTimer loop_timer;

int loop_num = 0;
int z_offset = 0;
int pos_mult = 0;
float z_speed = 0;

void one_dimensional() {
    unsigned int offset = analogRead(A0);
    Serial.print(offset);
    Serial.print(",");
    Serial.print(inoise8(offset));
    Serial.print(",");
    Serial.println(inoise8(offset + 16));
    delay(10);
}

void run_loop_timer() {
    loop_timer.update();
    loop_num++;
    if (loop_num > 15) {
        Serial.println(loop_timer.get_loop_time());
        loop_num = 0;
    }
}


void pot_z_offset_loop() {
    for (int index = 0; index < NUM_LEDS; index++) {
        int x = pgm_read_byte_near(LED_X_VALS + index) * pos_mult;
        int y = pgm_read_byte_near(LED_Y_VALS + index) * pos_mult;
        leds[index].setHSV(inoise8(x, y, z_offset), 255, 255);
    }
}

void z_speed_loop() {
    unsigned long current_millis = millis();
    float adjusted_millis = float(current_millis) * z_speed;
    for (int index = 0; index < NUM_LEDS; index++) {
        int x = pgm_read_byte_near(LED_X_VALS + index) * pos_mult;
        int y = pgm_read_byte_near(LED_Y_VALS + index) * pos_mult;
        leds[index].setHSV(inoise8(x, y, int(adjusted_millis)), 255, 255);
    }
}


void pot_z_offset_setup() {
    for (int index = 0; index < NUM_LEDS; index++) {
        leds[index] = CRGB::Black;
    }
}


void set_z_offset(int pot_value) {
    z_offset = pot_value;
}


void set_pos_mult(int pot_value) {
    pos_mult = map(pot_value, 0, 1023, 0, 20);
}


void set_z_speed(int pot_value) {
    z_speed = float(pot_value) / 1023.0;
}


void setup() {
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);

    red_pot.init();
    green_pot.init();

    pot_z_offset_setup();

    delay(50);
}


void loop() {
    // one_dimensional();

    // red_pot.update(&set_z_offset);
    // green_pot.update(&set_pos_mult);
    // pot_z_offset_loop();

    red_pot.update(&set_z_speed);
    green_pot.update(&set_pos_mult);
    z_speed_loop();

    FastLED.setBrightness(100);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
    FastLED.show();

    // run_loop_timer();



}