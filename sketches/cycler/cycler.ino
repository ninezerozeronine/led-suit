#include "cycler.h"

void min_reached(){
    Serial.println("min");
    Serial.println(millis());
}

void max_reached(){
    Serial.println("max");
    Serial.println(millis());	
}

Cycler cycler;

void setup() {
    // put your setup code here, to run once:
    cycler.init();
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    cycler.update(&min_reached, &max_reached);
}