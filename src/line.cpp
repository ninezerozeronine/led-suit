// Class that represents a line

#include "line.h"

Line::Line() {
    constructor_defaults();
}

Line::Line(float x_, float y_, float angle_) {
    constructor_defaults();
    x = x_;
    y = y_;
    angle = angle_;
    normal_needs_calculating = true;
    calculate_normal();
}

void Line::set_x(float x_) {
    x = x_;
}

void Line::set_y(float y_) {
    y = y_;
}

void Line::set_angle(float angle_) {
    angle = angle_;
    normal_needs_calculating = true;
}

float Line::get_x() {
    return x;
}

float Line::get_y(){
    return y;
}

float Line::get_angle(){
    return angle;
}

float Line::get_normal_x() {
    calculate_normal();
    return normal_x;
}

float Line::get_normal_y() {
    calculate_normal();
    return normal_y;
}

float Line::get_signed_distance(float point_x, float point_y) {
    // Using:
    // https://stackoverflow.com/questions/3860206/signed-distance-between-plane-and-point
    // https://en.wikipedia.org/wiki/Dot_product
    // dist = line_normal (dot) (point - line_origin)

    calculate_normal();

    float point_to_line_x = point_x - x;
    float point_to_line_y = point_y - y;
    float dot_product = (point_to_line_x * normal_x) + (point_to_line_y * normal_y);
    return dot_product;
}

void Line::constructor_defaults() {
    x = y = angle = normal_x = 0;
    normal_y = 1;
    normal_needs_calculating = false;
}
void Line::calculate_normal() {
    if (normal_needs_calculating) {
        // Convert angle to radians
        float radians = angle * 0.017453;
        normal_x = sin(radians);
        normal_y = cos(radians);
        normal_needs_calculating = false;
    }
}