#define NUM_STREAKERS 10


#include <FastLED.h>
#include <Arduino.h>

#include "constants.h"
#include "potentiometer.h"
#include "button.h"
// #include "loop_timer.h"

#include "modes/light_on_press.h"
#include "modes/linear_fill.h"
#include "modes/soft_rainbow_loop.h"
#include "modes/hard_rainbow_loop.h"
#include "modes/perlin.h"
#include "modes/streakers.h"
#include "modes/text_scroller.h"

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

Potentiometer brightness_pot(constants::BRIGHTNESS_POT_PIN);
Potentiometer pot_0(constants::POT_0_PIN);
Potentiometer pot_1(constants::POT_1_PIN);
Potentiometer pot_2(constants::POT_2_PIN);
Potentiometer pot_3(constants::POT_3_PIN);
Button button_0(constants::BUTTON_0_PIN);

Button mode_change_button(constants::MODE_CHANGE_PIN);

Mode * current_mode_ptr;

// unsigned long last_loop_print = 0;
// unsigned long loop_print_interval = 200;
// LoopTimer loop_timer;

int num_modes = 7;
int current_mode = num_modes - 1;

void setup() {
    Serial.begin(9600);
    // wait for serial port to connect. Needed for native USB port only
    while (!Serial) {
    ; 
    }
    FastLED.addLeds<NEOPIXEL, constants::LED_DATA_PIN>(leds, constants::NUM_LEDS);

    unsigned long current_millis = millis();

    brightness_pot.init();
    pot_0.init();
    pot_1.init();
    pot_2.init();
    pot_3.init();
    button_0.init();
    mode_change_button.init();

    delay(50);

    for(int index = 0; index < constants::NUM_LEDS; index++) {
        leds[index] = CRGB::Red;
    }

    current_mode_ptr = NULL;
    setup_next_mode();
    initialise_current_mode();
}

void loop() {
    // Serial.println(freeMemory());

    // loop_timer.update();
    // unsigned long current_millis = millis();
    // if ((current_millis - last_loop_print) > loop_print_interval) {
    //     Serial.println(loop_timer.get_loop_time());
    //     last_loop_print = current_millis;
    // }
    
    brightness_pot.update();
    pot_0.update(&pot_0_updated);
    pot_1.update(&pot_1_updated);
    pot_2.update(&pot_2_updated);
    pot_3.update(&pot_3_updated);
    button_0.update(&button_0_pressed, &button_0_released);

    current_mode_ptr->update();
    current_mode_ptr->apply_to_leds();

    int brightness = map(brightness_pot.get_value(), 0, 1023, 0, 255);
    FastLED.setBrightness(brightness);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 4000);
    FastLED.show();

    mode_change_button.update(&delete_current_mode);
    if (current_mode_ptr == NULL) {
        setup_next_mode();
        initialise_current_mode();
    }
}

void delete_current_mode(){
    if (current_mode_ptr != NULL) {
        delete current_mode_ptr;
        current_mode_ptr = NULL;
    }
}

void setup_next_mode(){
    current_mode = (current_mode + 1) % num_modes;
    Serial.println(current_mode);
    switch (current_mode){
        case 0:
            current_mode_ptr = new LightOnPress(leds);
            break;
        case 1:
            current_mode_ptr = new LinearFill(leds);
            break;
        case 2:
            current_mode_ptr = new SoftRainbowLoop(leds);
            break;
        case 3:
            current_mode_ptr = new HardRainbowLoop(leds);
            break;
        case 4:
            current_mode_ptr = new Perlin(leds);
            break;
        case 5:
            current_mode_ptr = new Streakers(leds);
            break;
        case 6:
            current_mode_ptr = new TextScroller(leds);
            break;
    }
}

void initialise_current_mode() {
    current_mode_ptr->initialise();
    current_mode_ptr->initialise_pot_0(pot_0.get_value());
    current_mode_ptr->initialise_pot_1(pot_1.get_value());
    current_mode_ptr->initialise_pot_2(pot_2.get_value());
    current_mode_ptr->initialise_pot_3(pot_3.get_value());
    current_mode_ptr->initialise_button_0(button_0.get_state());
}

void pot_0_updated(int new_val){
    current_mode_ptr->process_new_pot_0_value(new_val);
}

void pot_1_updated(int new_val){
    current_mode_ptr->process_new_pot_1_value(new_val);
}

void pot_2_updated(int new_val){
    current_mode_ptr->process_new_pot_2_value(new_val);
}

void pot_3_updated(int new_val){
    current_mode_ptr->process_new_pot_3_value(new_val);
}

void button_0_pressed(){
    current_mode_ptr->button_0_pressed();
}

void button_0_released(){
    current_mode_ptr->button_0_released();
}