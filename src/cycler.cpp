// Class to handle values that cycle over time
// Lerp formula = ((1-t) * A) + (t * b)
#include "cycler.h"

// Constructor
Cycler::Cycler(period=1000, min=0.0, max=255.0, cycle_mode=STATIC) {
    if (period < 1) {
        period = 1;
    }
    _period = period;
    _min = min;
    _max = max;
    _last_value = _min;
    _cycle_mode = cycle_mode;
    _duty = 0.5;
    _milli_progress = 0;
    _last_update = 0;
    _set_cycle_mode(_cycle_mode);
}


// Initialise the object
//
// Call this outside the constructor so caller has control when it runs
void Cycler::init() {
    _last_update = milis();
}

void Cycler::set_cycle_mode(cycle_t cycle_mode) {
    _cycle_mode = cycle_mode;
    _init_cycle();
}

void Cycler::_init_cycle() {
    switch (_cycle_mode) {
        case STATIC:
            _init_STATIC_cycle();
            break;
        case SIN:
            _init_SIN_cycle();
            break;
        case SAWTOOTH:
            _init_SAWTOOTH_cycle();
            break;
        case TRIANGLE:
            _init_TRIANGLE_cycle();
            break;
        case SQUARE:
            _init_SQUARE_cycle();
            break;
    }
}

void Cycler::_init_STATIC_cycle() {
    if (_value > _max) {
        _value = _max;
    }
    if (value < min) {
        value = min;
    }
}

void Cycler::_init_SIN_cycle() {

}

void Cycler::_init_SAWTOOTH_cycle(){
    _milli_progress = _normalised_progress * float(period);
}
void Cycler::_init_TRIANGLE_cycle();
void Cycler::_init_SQUARE_cycle();

// Get the current value of the cycler
float Cycler::get_value() {
    switch (_cycle_mode) {
        case STATIC:
            _calculate_STATIC();
            break;
        case SIN:
            _calculate_SIN();
            break;
        case SAWTOOTH:
            _calculate_SAWTOOTH();
            break;
        case TRIANGLE:
            _calculate_TRIANGLE();
            break;
        case SQUARE:
            _calculate_SQUARE();
            break;
    }
}

float _calculate_STATIC() {
    return _value;
}
void _calculate_SIN();
void _calculate_SAWTOOTH();
void _calculate_TRIANGLE();
float _calculate_SQUARE() {
    unsigned long timebase = millis() + offset;


}

// Set the minimum value that the cycler will reach
void Cycler::set_min(float min) {
    _min = min;
    _init_cycle();
}

// Set the maximum value that the cycler will reach
void Cycler::set_max(float max) {
    _max = max;
    _init_cycle();
}

// Set the period of the cycler
void Cycler::set_period(unsigned long period) {
    if (period < 1) {
        period = 1;
    }

    // Calculate how far through the current period we are and modify the offset
    // to keep the current value
    // Take into account the current offset too
    _period = period;
    _init_cycle();
}

// Set the progress through the period of the cycle
//
// Value ranges from 0 to 1 as a float
void Cycler::set_progress(float progress) {
    if (progress < 0) {
        progress = 0;
    }
    if (progress > 1) {
        progress = 1.0;
    }
    _milli_progress = progress * float(period);
    _normalised_progress = progress;
    _init_cycle();
}

// Set the progress through the period of the cycle
//
// Value ranges from 0 to period length
void Cycler::set_progress(unsigned long progress) {
    if (progress > period) {
        progress = period;
    }
    _milli_progress = progress;
    _normalised_progress = float(progress)/float(_period)
    _init_cycle();
}

// Call this once each time around the main arduino loop
void Cycler::update(void (*min_callback)()=NULL, void (*max_callback)()=NULL) {
    // Get how long it's been since the last update
    unsigned long current_time = millis();
    uint8_t elapsed_millis = current_time - _last_update;

    // If measurable time has passed
    if (elapsed_millis > 0) {
        // Store this read time
        _last_update = current_time;

        // Update based on current_mode
        switch (_mode) {
            case STATIC:
                // Nothing to do!
                break;
            case CYCLE_HUE:
                update_cycle_hue(elapsed_millis);
                break;
            case PULSE_VALUE:
                update_pulse_value(elapsed_millis);
                break;
            case PULSE_VALUE_CHANGE_HUE:
                update_pulse_value_change_hue(elapsed_millis);
                break;
            case PULSE_VALUE_CYCLE_HUE:
                update_pulse_value_change_hue(elapsed_millis);
                break;
        }
    }
}

void Cycler::_update_sin(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
void Cycler::_update_sawtooth(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
void Cycler::_update_triangle(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
void Cycler::_update_square(void (*min_callback)()=NULL, void (*max_callback)()=NULL);

void Cycler::_reconfigure() {
    // Update offset to account for period changing
    // Recalculate min/max milli marks for callback calculation in update
}
