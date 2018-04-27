#include <Arduino.h>

#include "cycler.h"

Cycler spawn_timer;

void triggered() {
    Serial.println(-2);
}

void setup() {
    Serial.begin(9600);
    spawn_timer.init();
    spawn_timer.set_max(2);
    spawn_timer.set_cycle_mode(Cycler::SQUARE);
    spawn_timer.set_period_immediate(428);
}

void loop() {
    spawn_timer.update(&triggered);
    Serial.println(spawn_timer.get_value());
    delay(random(10,31));
}

    // Serial.println(spawn_timer._calculate_normalised_progress());
