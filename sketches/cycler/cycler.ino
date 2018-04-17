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
bool changed = false;
unsigned long num = 0;

void setup() {
    // put your setup code here, to run once:
    cycler.init();
    // cycler.set_cycle_mode(Cycler::SQUARE);
    // cycler.set_duty(0.25);

    cycler.set_cycle_mode(Cycler::TRIANGLE);
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    // cycler.update(&min_reached, &max_reached);

    // if (millis() > 10000 && !changed) {
    //     cycler.set_duty(0.25);
    //     changed = true;
    // }

    // num++;
    // if (num % 5000 == 0) {
    //     Serial.println("---");
    //     Serial.println(millis());
    //     Serial.println("---");
    // }

    // if (millis() > 12345 && !changed) {
    //     cycler.set_period(2000, true);
    //     changed = true;
    // }

    if (num % 10000 == 0) {
        cycler.set_period(random(500, 2500), true);
    }

    // if ((num + 5000) % 10000 == 0) {
        
    // }



    if (num % 50 == 0) {
        Serial.println("---");
        Serial.println(cycler.get_value());
        Serial.println("---");
    }

    num++;
}