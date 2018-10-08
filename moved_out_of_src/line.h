// Class that represents a line

#ifndef line_h
#define line_h

#include <Arduino.h>

class Line {
    public:
        Line();
        Line(float x_, float y_, float angle_);
        void set_x(float x_);
        void set_y(float y_);
        void set_angle(float angle_);
        float get_x();
        float get_y();
        float get_angle();
        float get_normal_x();
        float get_normal_y();
        float get_signed_distance(float point_x, float point_y);

    private:
        bool normal_needs_calculating;
        float x;
        float y;
        float angle;
        float normal_x;
        float normal_y;

        void constructor_defaults();
        void calculate_normal();
};

#endif