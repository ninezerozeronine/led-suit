#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

namespace constants {
    // We need to define this here as extern consts are not compile time
    // constants so we can't initialise arrays with them.
    //
    // FastLED.addLeds also seems to befussy about the data pin it's
    // passed
    const int NUM_LEDS = 256;
    const byte LED_DATA_PIN = 2;

    extern const byte POT_0_PIN;
    extern const byte POT_1_PIN;
    extern const byte POT_2_PIN;
    extern const byte POT_3_PIN;
    extern const byte POT_4_PIN;
    extern const byte BUTTON_0_PIN;

    extern const byte MODE_CHANGE_PIN;

    extern const byte LED_X_VALS[];
    extern const byte LED_Y_VALS[];
}

#endif
