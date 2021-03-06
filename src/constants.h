#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

#define OUTPUT_SUIT
// #define OUTPUT_64_GRID
// #define OUTPUT_256_GRID

namespace constants {
    // We need to define this here as extern consts are not compile time
    // constants so we can't initialise arrays with them.
    //
    // FastLED.addLeds also seems to be fussy about the data pin it's
    // passed
    #ifdef OUTPUT_SUIT
        const int NUM_LEDS = 366;
    #endif

    #ifdef OUTPUT_64_GRID
        const int NUM_LEDS = 64;
    #endif

    #ifdef OUTPUT_256_GRID
        const int NUM_LEDS = 256;
    #endif


    const byte LED_DATA_PIN = 2;

    extern const byte GRID_WIDTH;
    extern const byte GRID_HEIGHT;

    extern const byte BRIGHTNESS_POT_PIN;
    extern const byte POT_0_PIN;
    extern const byte POT_1_PIN;
    extern const byte POT_2_PIN;
    extern const byte POT_3_PIN;
    extern const byte BUTTON_0_PIN;
    extern const byte BUTTON_1_PIN;
    extern const byte BUTTON_2_PIN;

    extern const byte MODE_CHANGE_PIN;

    extern const byte LED_X_VALS[];
    extern const byte LED_Y_VALS[];

    extern const int LED_GRID_INDECIES[];

    extern const int CHAR_WIDTH;
    extern const int CHAR_HEIGHT;
    extern const int NUM_MESSAGES;
    extern const byte HORIZ_TOP_LEFT_ROW;
    extern const byte HORIZ_TOP_LEFT_COLUMN;
    extern const byte HORIZ_DISPLAY_WIDTH;
    extern const byte VERT_TOP_LEFT_ROW;
    extern const byte VERT_TOP_LEFT_COLUMN;
    extern const byte VERT_DISPLAY_WIDTH;
    extern const char MESSAGE_0[];
    extern const char MESSAGE_1[];
    extern const char MESSAGE_2[];
    extern const char* const MESSAGES[];
    extern const byte ASCII_CHARS[];
}

#endif
