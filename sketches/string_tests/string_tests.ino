#include "Arduino.h"
#include <avr/pgmspace.h>

const char string_0[] PROGMEM = "String 0";   // "String 0" etc are strings to store - change to suit.
const char string_1[] PROGMEM = "Blah";
const char string_2[] PROGMEM = "Foo .";
const char string_3[] PROGMEM = "String 3";
const char string_4[] PROGMEM = "String 4";
const char string_5[] PROGMEM = "String 5";
const char* const string_table[] PROGMEM = {string_0, string_1, string_2, string_3, string_4, string_5};
char buffer[30]; 

const byte LETTER[8] = {
    B00111100,
    B01000010,
    B01000010,
    B01111110,
    B01000010,
    B01000010,
    B01000010,
    B01000010
};

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);

    // wait for serial port to connect. Needed for native USB port only
    while (!Serial) {
    ; 
    }
    Serial.println("OK");

    for (int row = 0; row < 8; row++) {
        for (int column = 0; column < 8; column++) {
            if (LETTER[row] >> column & 1 == 1) {
                Serial.print("O");
            }
            else {
                Serial.print(" ");
            }
        }
        Serial.println("");
    }
}

void loop() {
    // put your main code here, to run repeatedly:
  for (int i = 0; i < 6; i++)
  {
    strcpy_P(buffer, (char*)pgm_read_word(&(string_table[i]))); // Necessary casts and dereferencing, just copy.
    Serial.println(strlen(buffer));
    Serial.println(int(buffer[0]));
    Serial.println(buffer);
    Serial.println("");
    delay( 500 );
  }
}