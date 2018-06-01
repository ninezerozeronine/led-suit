#include <FastLED.h>
#include <Arduino.h>

#include "constants.h"
#include "potentiometer.h"
#include "button.h"

#include "light_on_press.h"
#include "linear_fill.h"

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__
 
int freeMemory() {
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}

CRGB leds[constants::NUM_LEDS];

Potentiometer pot_0(constants::POT_0_PIN);
Potentiometer pot_1(constants::POT_1_PIN);
Potentiometer pot_2(constants::POT_2_PIN);
Potentiometer pot_3(constants::POT_3_PIN);
Potentiometer pot_4(constants::POT_4_PIN);
Button button_0(constants::BUTTON_0_PIN);

Button mode_change_button(constants::MODE_CHANGE_PIN);

Mode * current_mode_ptr;

int num_modes = 2;
int current_mode = 0;

void setup() {
    Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, constants::LED_DATA_PIN>(leds, constants::NUM_LEDS);

    pot_0.init();
    pot_1.init();
    pot_2.init();
    pot_3.init();
    pot_4.init();
    button_0.init();
    mode_change_button.init();

    delay(50);

    for(int index = 0; index < constants::NUM_LEDS; index++) {
        leds[index] = CRGB::Red;
    }

    current_mode_ptr = new LightOnPress(leds);
}

void loop() {
    Serial.println(freeMemory());

    unsigned long current_millis = millis();

    pot_0.update(&pot_0_updated);
    pot_1.update(&pot_1_updated);
    pot_2.update(&pot_2_updated);
    pot_3.update(&pot_3_updated);
    pot_4.update(&pot_4_updated);
    button_0.update(&button_0_pressed, &button_0_released);

    current_mode_ptr->update(current_millis);

    FastLED.setBrightness(128);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 1000);
    FastLED.show();

    mode_change_button.update(&next_mode);
}


void next_mode(){
    delete current_mode_ptr;
    current_mode = (current_mode + 1) % num_modes;
    switch (current_mode){
        case 0:
            current_mode_ptr = new LightOnPress(leds);
            break;
        case 1:
            current_mode_ptr = new LinearFill(leds);
            break;
    }
}


void pot_0_updated(uint16_t new_val){
    current_mode_ptr->pot_0(new_val);
}

void pot_1_updated(uint16_t new_val){
    current_mode_ptr->pot_1(new_val);
}

void pot_2_updated(uint16_t new_val){
    current_mode_ptr->pot_2(new_val);
}

void pot_3_updated(uint16_t new_val){
    current_mode_ptr->pot_3(new_val);
}

void pot_4_updated(uint16_t new_val){
    current_mode_ptr->pot_4(new_val);
}

void button_0_pressed(){
    current_mode_ptr->button_0_pressed();
}

void button_0_released(){
    current_mode_ptr->button_0_released();
}