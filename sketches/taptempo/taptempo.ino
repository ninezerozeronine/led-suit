#include "button.h"
#include "cycler.h"
#include "taptempo.h"

#define BUTTON_PIN 3

Cycler cycler_driver, cycler_driven;
Button button(BUTTON_PIN);
TapTempo taptempo;
int taps = 0;
unsigned long last_val_print = 0;


void drive_tapper() {
    taptempo.tap();
    cycler_driven.set_period_gradual(taptempo.get_period());
    cycler_driven.set_offset_gradual(taptempo.get_offset());
} 

void tempo_pickup_test_setup() {
    cycler_driver.init();
    cycler_driver.set_period_immediate(982);
    cycler_driver.set_offset_immediate(658);
    cycler_driver.set_duty(0.1);
    cycler_driver.set_cycle_mode(Cycler::SQUARE);

    cycler_driven.init();
    cycler_driven.set_period_immediate(3000);
    cycler_driven.set_cycle_mode(Cycler::TRIANGLE);
}

void tempo_pickup_test_loop() {
    if ((taps < 10) && millis() > 5000) {
        cycler_driver.update(NULL, &drive_tapper);
        taps++;
    } else {
        cycler_driver.update();
    }
    cycler_driven.update();

    Serial.print(cycler_driver.get_value());
    Serial.print(",");
    Serial.println(cycler_driven.get_value());

    // unsigned long current_time = millis();
    // if ((current_time - last_val_print) > 500) {
    //     last_val_print = current_time;
    //     Serial.println("---");
    //     Serial.println(taptempo.get_period());
    //     Serial.println(taptempo.get_offset());
    // }
}

void button_driver_numbers_setup() {
    // this comment allows folding
    button.init();
}

void button_driver_numbers_loop() {
    button.update(&drive_tapper);
    unsigned long current_time = millis();
    if ((current_time - last_val_print) > 500) {
        last_val_print = current_time;
        Serial.println("---");
        Serial.println(taptempo.get_period());
        Serial.println(taptempo.get_offset());
    }
}

void button_driver_graph_setup() {
    button.init();
    cycler_driven.init();
    cycler_driven.set_period_immediate(1000);
    cycler_driven.set_cycle_mode(Cycler::TRIANGLE);
}

void button_driver_graph_loop() {
    button.update(&drive_tapper);
    cycler_driven.update();
    Serial.println(cycler_driven.get_value());
}

void setup() {
    // put your setup code here, to run once:

    // tempo_pickup_test_setup();
    // button_driver_numbers_setup();
    button_driver_graph_setup();
    Serial.begin(9600);

}

void loop() {
    // put your main code here, to run repeatedly:

    // tempo_pickup_test_loop();
    // button_driver_numbers_loop();
    button_driver_graph_loop();
}