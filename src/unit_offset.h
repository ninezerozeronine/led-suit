#ifndef UNIT_OFFSET_H
#define UNIT_OFFSET_H

#include <Arduino.h>

class UnitOffset {
    public:
        UnitOffset();
        UnitOffset(float speed);
        void init();
        void update();
        float apply_offset(float original);
        void set_speed(float speed_);
    private:
        void constructor_defaults();
        float restore_to_unit_range(float value);
        unsigned long last_update;
        float offset;
        float speed;
};

#endif