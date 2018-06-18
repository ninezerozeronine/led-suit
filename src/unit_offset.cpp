#include "unit_offset.h"

UnitOffset::UnitOffset() {
    constructor_defaults();
}

UnitOffset::UnitOffset(float speed_) {
    constructor_defaults();
    speed = speed_;
}

void UnitOffset::constructor_defaults() {
    last_update = 0;
    offset = 0;
    speed = 0.001;
}

void UnitOffset::init() {
    last_update = millis();
}

void UnitOffset::update() {
    unsigned long current_millis = millis();
    byte elapsed_millis = current_millis - last_update;
    offset += speed * elapsed_millis;
    offset = restore_to_unit_range(offset);
    last_update = current_millis;
}

float UnitOffset::apply_offset(float original) {
    float new_value = original + offset;
    new_value = restore_to_unit_range(new_value);
    return new_value;
}

void UnitOffset::set_speed(float speed_) {
    speed = speed_;
}

float UnitOffset::restore_to_unit_range(float value) {
    if (value >= 1.0) {
        value = value - 1.0;
    } else if (value < 0.0) {
        value = value + 1.0;
    }
    return value;
}