#include "button.h"

void button_pressed(){
    Serial.println("Button pressed");
    Serial.println(millis());
}

void button_released(){
    Serial.println("Button released");
    Serial.println(millis());	
}

int BUTTON_PIN = 2;
Button button(BUTTON_PIN, 10);

void setup() {
    // put your setup code here, to run once:
    button.init();
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    button.update(&button_pressed, &button_released);
}