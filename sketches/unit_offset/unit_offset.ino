#include "unit_offset.h"
#include "potentiometer.h"

#define INPUT_POT_PIN A0
#define SPEED_POT_PIN A1

UnitOffset unit_offset;

void setup() {
    Serial.begin(9600);
    unit_offset.init();
    delay(50);
}

void loop() {
    unit_offset.update();
    float input = float(analogRead(INPUT_POT_PIN))/1024.0;
    float offset_val = unit_offset.apply_offset(input);

    int value = analogRead(SPEED_POT_PIN);
    int dead_min = 500;
    int dead_max = 520;
    float max_speed = 0.005;
    float speed = 0;
    if (value < dead_min) {
        int dist_from_dead_min = dead_min - value;
        float normalised = float(dist_from_dead_min) / float(dead_min);
        speed = -1.0 * normalised * max_speed;
    } else if (value > dead_max) {
        int dist_from_dead_max = value - dead_max;
        float normalised = float(dist_from_dead_max) / float(1023 - dead_max);
        speed = normalised * max_speed;
    }
    unit_offset.set_speed(speed);

    Serial.print(input);
    Serial.print(",");
    // Serial.print(speed);
    // Serial.print(",");
    Serial.println(offset_val);
    // Serial.println(speed);
}