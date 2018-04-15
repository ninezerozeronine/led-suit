#include "potentiometer.h"
#include "Arduino.h"

void print_change(uint8_t new_val){
    Serial.println(new_val);
}

Potentiometer pot(A1, 10, &print_change);

void setup() {
    // put your setup code here, to run once:
    pot.init();
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
     pot.update();
}