#include "button.h"
#include "cycler.h"
#include "taptempo.h"


Cycler cycler_driver, cycler_driven;
TapTempo taptempo;
int taps = 0;
void drive_tapper(){
	if (taps < 10) {
	    taptempo.tap();
	    cycler_driven.set_period(taptempo.get_period());
	    cycler_driven.set_offset(taptempo.get_offset());
	    ++taps;
	} else {
		Serial.print(taptempo.get_period());
		Serial.print(",");
		Serial.println(taptempo.get_offset());
	}
}

void setup() {
    // put your setup code here, to run once:
    cycler_driver.init();
    cycler_driven.init();
    cycler_driven.set_period(3000);
    cycler_driver.set_offset(321);
    cycler_driver.set_duty(0.1);

    cycler_driver.set_cycle_mode(Cycler::SQUARE);
	cycler_driven.set_cycle_mode(Cycler::TRIANGLE);
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    cycler_driver.update(NULL, &drive_tapper);
    // Serial.print(cycler_driver.get_value());
    // Serial.print(",");
    // Serial.println(cycler_driven.get_value());
}




// Cycler cycler_driver, cycler_driven;
// TapTempo taptempo;
// int taps = 0;
// // unsigned long num = 0;
// void drive_tapper(){
// 	Serial.println(millis());
// }

// void setup() {
//     // put your setup code here, to run once:
//     cycler_driver.init();
//     cycler_driven.init();
//     cycler_driven.set_period(3000);
//     cycler_driver.set_offset(250);

//     cycler_driver.set_cycle_mode(Cycler::SQUARE);
// 	cycler_driven.set_cycle_mode(Cycler::TRIANGLE);
//     Serial.begin(9600);
// }

// void loop() {
//     // put your main code here, to run repeatedly:
//     cycler_driver.update(NULL, &drive_tapper);
// }


// #define BUTTON_PIN 2
// Button button(BUTTON_PIN, 10);
// Cycler cycler;
// TapTempo taptempo;

// void button_pressed(){
//     taptempo.tap();

//     // Serial.println(millis());
// 	// Serial.println(taptempo.get_period());

//     cycler.set_period(taptempo.get_period());
//     cycler.set_offset(taptempo.get_offset());
// }

// void setup() {
//     // put your setup code here, to run once:
//     button.init();
//     cycler.init();
//     cycler.set_cycle_mode(Cycler::TRIANGLE);
//     Serial.begin(9600);
// }

// void loop() {
//     // put your main code here, to run repeatedly:
//     button.update(&button_pressed);
//     Serial.println(cycler.get_value());
// }