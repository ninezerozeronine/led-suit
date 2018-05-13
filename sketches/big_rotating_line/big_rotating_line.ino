#include <FastLED.h>
#include <Arduino.h>

#include "potentiometer.h"
#include "line.h"

#define NUM_LEDS 256
#define LED_DATA_PIN 2
#define LINE_X_POS_POT_PIN A0
#define LINE_Y_POS_POT_PIN A1
#define LINE_ANGLE_POT_PIN A2

const byte LED_X_VALS[NUM_LEDS] = {
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

const byte LED_Y_VALS[NUM_LEDS] = {
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
Potentiometer line_angle_pot(LINE_ANGLE_POT_PIN);
Potentiometer line_x_pos_pot(LINE_X_POS_POT_PIN);
Potentiometer line_y_pos_pot(LINE_Y_POS_POT_PIN);
Line line(0, 0, 0);

void set_line_angle(int pot_value) {
    int angle = map(pot_value, 0, 1023, 0, 359);
    line.set_angle(angle);
}

void set_line_x_pos(int pot_value) {
    int x = map(pot_value, 0, 1023, -10, 265);
    line.set_x(x);
}

void set_line_y_pos(int pot_value) {
    int y = map(pot_value, 0, 1023, -10, 265);
    line.set_y(y);
}

void colour_LEDs_by_line_red_blue() {
    for (int index = 0; index < NUM_LEDS; index++) {
        float distance = line.get_signed_distance(LED_X_VALS[index], LED_Y_VALS[index]);
        if (distance > 0) {
            leds[index] = CRGB::Red;
        } else {
            leds[index] = CRGB::Blue;
        }
    }
}

void colour_LEDs_by_line_fade_white() {
    for (int index = 0; index < NUM_LEDS; index++) {
        int distance = int(line.get_signed_distance(LED_X_VALS[index], LED_Y_VALS[index]));
        distance = abs(distance);
        if (distance > 100) {
            leds[index] = CRGB::Black;
        } else {
            int value = map(distance, 0, 100, 0, 255);
            leds[index].setHSV(0,0,255-value);
        }
    }
}

void colour_LEDs_by_rainbow() {
    for (int index = 0; index < NUM_LEDS; index++) {
        int distance = int(line.get_signed_distance(LED_X_VALS[index], LED_Y_VALS[index]));
        distance = abs(distance);
        leds[index].setHSV((distance % 256),255,255);
    }
}


void setup() {
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);

    line_angle_pot.init();
    line_x_pos_pot.init();
    line_y_pos_pot.init();

    delay(50);

    for(int index = 0; index < NUM_LEDS; index++) {
        leds[index] = CRGB::Black;
    }

    set_line_angle(line_angle_pot.get_value());
    set_line_x_pos(line_x_pos_pot.get_value());
    set_line_y_pos(line_y_pos_pot.get_value());
}

void loop() {
    line_angle_pot.update(&set_line_angle);
    line_x_pos_pot.update(&set_line_x_pos);
    line_y_pos_pot.update(&set_line_y_pos);

    // colour_LEDs_by_line_red_blue();
    colour_LEDs_by_line_fade_white();
    // colour_LEDs_by_rainbow();

    FastLED.setBrightness(100);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
    FastLED.show();

}