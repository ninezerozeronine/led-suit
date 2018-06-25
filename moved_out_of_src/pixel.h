// Class to that represents an individual pixel

#ifndef pixel_h
#define pixel_h

#include <Arduino.h>

class Pixel {
    public:
        Pixel();
    private:
        byte x;
        byte y;
        byte distance_from_centre;
};

#endif