float LinearMapper::floating_modulo(float input, int max) {
    // Do a floating point modulo 0 -> (max - (a tiny bit))
    int int_part = int(input);
    float decimal_part = input - int_part;
    int wrapped = int_part % max;
    float wrapped_float = wrapped + decimal_part;
    return wrapped_float;
}

float LinearMapper::get_value_at(int query_value){
    // Loop the query value to max_value
    int wrapped_to_length = query_value % max_value;

    // Normalise the result
    float normalised = float(max_value) / float(wrapped_to_length);

    // Add the offset and wrap
    float with_offset = restore_to_unit_range(normalised + offset);

    return with_offset;
}

float restore_to_unit_range(float value) {
    if (value >= 1.0) {
        value = value - 1.0;
    } else if (value < 0.0) {
        value = value + 1.0;
    }
}

void LinearMapper::set_max_value(float max_value_) {
    max_value = max_value_;
}

void update_offset(unsigned long elapsed_millis) {
    offset = offset + (elapsed_millis * speed);
    offset = restore_to_unit_range(offset);
}

void set_speed(float speed_) {
    speed = speed_;
}


// int wrap_query_to_length(int query) {
//     return query % length;
// }

// query_position = floating_modulo(view_position + offset, length);
// normalised_position = query_position / length;