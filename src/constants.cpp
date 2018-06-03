#include "constants.h"

namespace constants {
    extern const byte POT_0_PIN = A0;
    extern const byte POT_1_PIN = A1;
    extern const byte POT_2_PIN = A2;
    extern const byte POT_3_PIN = A3;
    extern const byte POT_4_PIN = A6;
    extern const byte BUTTON_0_PIN = 4;

    extern const byte MODE_CHANGE_PIN = 3;

    extern const byte LED_X_VALS[NUM_LEDS] PROGMEM = {
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

    extern const byte LED_Y_VALS[NUM_LEDS] PROGMEM = {
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
}