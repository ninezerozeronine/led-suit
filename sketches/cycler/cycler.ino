#include "cycler.h"

Cycler cycler1, cycler2, cycler3, cycler4, cycler5;
bool changed = false;
unsigned long num = 0;
unsigned long last_millis = 0;
unsigned long last_period_change = 0;
unsigned long last_offset_change = 0;
unsigned long last_val_print = 0;

void min_reached() {
    Serial.println("-128");
    //Serial.println(millis());
}

void max_reached() {
    Serial.println("383");
    //Serial.println(millis());   
}

void ticker() {
    // A higher than normal tick to see timing
    Serial.println("450");
}

void print_min_millis() {
    Serial.print("Min: ");
    Serial.println(millis());
}

void print_max_millis() {
    Serial.print("Max: ");
    Serial.println(millis());
}

void five_cyclers_setup() {
    cycler1.init();
    cycler2.init();
    cycler3.init();
    cycler4.init();
    cycler5.init();

    Cycler::mode_t cycle_mode = Cycler::TRIG;
    cycler1.set_cycle_mode(cycle_mode);
    cycler2.set_cycle_mode(cycle_mode);
    cycler3.set_cycle_mode(cycle_mode);
    cycler4.set_cycle_mode(cycle_mode);
    cycler5.set_cycle_mode(cycle_mode);
}

void five_cyclers_loop() {
	// 5 cyclers updating and getting each time round the loop:
	// in sin or triangle mode runs at about 2ms per loop
	// in static mode 0.14ms per loop
	// in square mode 0.14ms per loop
	// the mushroom lamp runs at about 2.5 ms per loop
    cycler1.update();
    cycler1.get_value();
    cycler2.update();
    cycler2.get_value();
    cycler3.update();
    cycler3.get_value();
    cycler4.update();
    cycler4.get_value();
    cycler5.update();
    cycler5.get_value();

    uint16_t num_loops = 1000;
    if (num % num_loops == 0) {
        unsigned long current_millis = millis();
        long num_millis = current_millis - last_millis;
        float ms_per_cycle = float(num_millis) / float(num_loops);
        Serial.println(ms_per_cycle);
        last_millis = current_millis;
    }

    num++;
}

void cycle_types_setup() {
    cycler1.init();
    cycler2.init();
    cycler3.init();
    cycler4.init();

    cycler1.set_period(5000);
    cycler2.set_period(5000);
    cycler3.set_period(5000);
    cycler4.set_period(5000);

    cycler1.set_cycle_mode(Cycler::STATIC);
    cycler2.set_cycle_mode(Cycler::SQUARE);
    cycler3.set_cycle_mode(Cycler::TRIANGLE);
    cycler4.set_cycle_mode(Cycler::TRIG);
}

void cycle_types_loop() {
    cycler1.update();
    cycler2.update();
    cycler3.update();
    cycler4.update();
    
	Serial.print(cycler1.get_value());
	Serial.print(",");
	Serial.print(cycler2.get_value());
	Serial.print(",");
	Serial.print(cycler3.get_value());
	Serial.print(",");
	Serial.println(cycler4.get_value());
}

void change_period_detect_minmax_setup() {
    cycler1.init();
    cycler1.set_cycle_mode(Cycler::TRIANGLE);
}

void change_period_detect_minmax_loop() {
    cycler1.update(&min_reached, &max_reached);

    unsigned long current_millis = millis();

    if (current_millis - last_period_change > 5000) {
        cycler1.set_period(random(500, 2500), true);
        last_period_change = current_millis;
    }

    if (current_millis - last_val_print > 10) {
        Serial.println(cycler1.get_value());
        last_val_print = current_millis;
    }
}

void gradual_offset_setup() {
    cycler1.init();
    cycler1.set_cycle_mode(Cycler::TRIG);
    cycler1.set_period(1000);

    cycler2.init();
    cycler2.set_cycle_mode(Cycler::TRIG);
    cycler2.set_period(1000);
}

void gradual_offset_loop() {
    // cycler1.update(&min_reached, &max_reached);
    // cycler2.update(NULL, &ticker);

    cycler1.update();
    cycler2.update();

    unsigned long current_millis = millis();
    if (current_millis - last_offset_change > 10000) {
        bool gradual = true;
        uint16_t new_offset = random(0,1000);
        cycler1.set_offset(new_offset);
        cycler1.set_target_offset(new_offset);
        cycler2.set_target_offset(new_offset);
        last_offset_change = current_millis;
    }

    if (current_millis - last_val_print > 10) {
        Serial.print(cycler1.get_value());
        // Serial.print(cycler1.get_period());
        Serial.print(",");
        Serial.println(cycler2.get_value());
        // Serial.println(cycler2.get_period());
        last_val_print = current_millis;
    }
}

void gradual_period_setup() {
    cycler1.init();
    cycler1.set_cycle_mode(Cycler::TRIG);
    cycler1.set_period(1000);

    cycler2.init();
    cycler2.set_cycle_mode(Cycler::TRIG);
    cycler2.set_period(1000);
}

void gradual_period_loop() {
    //cycler1.update(&min_reached, &max_reached);
    cycler1.update();
    // cycler2.update(NULL, &ticker);
    cycler2.update();

    unsigned long current_millis = millis();
    if (current_millis - last_period_change > 10000) {
        //Serial.println(350);
        bool maintain_progress = false;
        bool gradual = true;
        uint16_t new_period = random(500,5000);
        cycler1.set_period(new_period);
        cycler1.set_target_period(new_period);
        cycler2.set_target_period(new_period);
        last_period_change = current_millis;
    }

    if (current_millis - last_val_print > 10) {
        Serial.print(cycler1.get_value());
        // Serial.print(cycler1.get_period());
        Serial.print(",");
        Serial.println(cycler2.get_value());
        // Serial.println(cycler2.get_period());
        last_val_print = current_millis;
    }
}

void setup() {
    // put your setup code here, to run once:
	// five_cyclers_setup();
	// cycle_types_setup();
    // change_period_detect_minmax_setup();
    gradual_offset_setup();
    // gradual_period_setup();
    Serial.begin(9600);
}

    // cycler.set_cycle_mode(Cycler::SQUARE);
    // cycler.set_duty(0.25);

void loop() {
    // put your main code here, to run repeatedly:
    // five_cyclers_loop();
    // cycle_types_loop();
    // change_period_detect_minmax_loop();
    gradual_offset_loop();
    // gradual_period_loop();

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

    // if (millis() > 12345 && !changed) {
    //     cycler1.set_period(3000, true);
    //     changed = true;
    // }



    // if ((num + 5000) % 10000 == 0) {
        
    // }



    // if (num % 50 == 0) {
    //     Serial.println(cycler1.get_value());
    // }

    // num++;
}