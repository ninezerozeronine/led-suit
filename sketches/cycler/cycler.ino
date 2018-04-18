#include "cycler.h"
// 5 cyclers updating and getting each time round the loop:
// in sin or triangle mode runs at about 2ms per loop
// in static mode 0.14ms per loop
// in square mode 0.14ms per loop
// the mushroom lamp runs at about 2.5 ms per loop

void min_reached(){
    //Serial.println("-128");
    //Serial.println(millis());
}

void max_reached(){
    //Serial.println("383");
    //Serial.println(millis());   
}

Cycler cycler1, cycler2, cycler3, cycler4, cycler5;
bool changed = false;
unsigned long num = 0;
long last_millis = 0;

void setup() {
    // put your setup code here, to run once:
    cycler1.init();
    cycler2.init();
    cycler3.init();
    cycler4.init();
    cycler5.init();
    // cycler.set_cycle_mode(Cycler::SQUARE);
    // cycler.set_duty(0.25);

    // cycler1.set_cycle_mode(Cycler::SIN);
    // cycler2.set_cycle_mode(Cycler::SIN);
    // cycler3.set_cycle_mode(Cycler::SIN);
    // cycler4.set_cycle_mode(Cycler::SIN);
    // cycler5.set_cycle_mode(Cycler::SIN);
    // cycler1.set_cycle_mode(Cycler::TRIANGLE);
    // cycler2.set_cycle_mode(Cycler::TRIANGLE);
    // cycler3.set_cycle_mode(Cycler::TRIANGLE);
    // cycler4.set_cycle_mode(Cycler::TRIANGLE);
    // cycler5.set_cycle_mode(Cycler::TRIANGLE);
    cycler1.set_cycle_mode(Cycler::SQUARE);
    cycler2.set_cycle_mode(Cycler::SQUARE);
    cycler3.set_cycle_mode(Cycler::SQUARE);
    cycler4.set_cycle_mode(Cycler::SQUARE);
    cycler5.set_cycle_mode(Cycler::SQUARE);
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    cycler1.update(&min_reached, &max_reached);
    cycler1.get_value();
    cycler2.update(&min_reached, &max_reached);
    cycler2.get_value();
    cycler3.update(&min_reached, &max_reached);
    cycler3.get_value();
    cycler4.update(&min_reached, &max_reached);
    cycler4.get_value();
    cycler5.update(&min_reached, &max_reached);
    cycler5.get_value();

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

    if (millis() > 12345 && !changed) {
        cycler1.set_period(3000, true);
        changed = true;
    }

    if (num % 10000 == 0) {
        // cycler.set_period(random(500, 2500), true);
        unsigned long current_millis = millis();
        long num_millis = current_millis - last_millis;
        float ms_per_cycle = float(num_millis) / 10000.0;
        Serial.println(ms_per_cycle);
        last_millis = current_millis;
    }

    // if ((num + 5000) % 10000 == 0) {
        
    // }



    // if (num % 50 == 0) {
    //     Serial.println("---");
    //     Serial.println(cycler.get_value());
    //     Serial.println("---");
    // }

    num++;
}