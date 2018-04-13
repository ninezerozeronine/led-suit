#include <button.h>

void blah(){
    Serial.println("Button Pressed");
    Serial.println(millis());
}

int BUTTON_PIN = 2;
Button button(BUTTON_PIN, 50, &blah);

void setup() {
    // put your setup code here, to run once:
    button.init();
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    button.update();
}