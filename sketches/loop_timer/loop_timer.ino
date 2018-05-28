#include <Arduino.h>

#include "loopTimer.h"

LoopTimer loop_timer;
int num;

void setup() {
    Serial.begin(9600);
}

void loop() {
    loop_timer.update();
    delay(15);
    num++;
    if (num > 15) {
        Serial.println(loop_timer.get_loop_time());
        num = 0;
    }
}