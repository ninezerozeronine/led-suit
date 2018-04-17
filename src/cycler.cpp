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
    // _last_value = _min;
    _cycle_mode = cycle_mode;
    _duty = 0.5;
    _milli_progress = 0;
    _last_update = 0;
    //_last_milli_progress = 0;
    _last_normalised_progress = 0.0;
    _callbacks_invalidated = false;
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
}

void Cycler::set_period(cycle_t cycle_mode) {
    _cycle_mode = cycle_mode;
}

// Get the current value of the cycler
float Cycler::get_value() {
    switch (_cycle_mode) {
        case STATIC:
            _calculate_STATIC();
            break;
        case SIN:
            _calculate_SIN();
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
}

// Set the maximum value that the cycler will reach
void Cycler::set_max(float max) {
    _max = max;
}

void Cycler::set_duty(float duty) {
    _callbacks_invalidated = true;
}


void Cycler::start_period_now(){
    _callbacks_invalidated = true;
}

// Set the period of the cycler
void Cycler::set_period(unsigned long period, bool maintain_progress=false) {
    if (period < 1) {
        period = 1;
    }

    if (maintain_progress) {
        // How far through the current period are we right now
        unsigned long current_time = millis()
        unsigned long cycler_time = current_time + _milli_offset;
        unsigned long old_period_time = cycler_time % _period;
        float period_progress = float(old_period_time)/float(_period);

        // Calculate offset to get us to the same point in the period
        unsigned long new_period_time = period * period_progress;
        unsigned long non_offset_new_period_time = current_time % period;
        long new_offset = new_period_time - non_offset_new_period_time;

        // Ensure offset is +ve
        if (new_offset < 0) {
            new_offset += period;
        }

        _milli_offset = unsigned long(new_offset);
    }

    _period = period;
    _callbacks_invalidated = true;
}

// Call this once each time around the main arduino loop
void Cycler::update(void (*min_callback)()=NULL, void (*max_callback)()=NULL) {
    // Get how long it's been since the last update
    unsigned long current_time = millis();
    uint8_t elapsed_millis = current_time - _last_update;

    // If measurable time has passed
    if (elapsed_millis > 0) {
        if (!_callbacks_invalidated) {
            // Update based on current_mode
            switch (_mode) {
                case STATIC:
                    // Nothing to do!
                    break;
                case SIN:
                    _update_sin(min_callback, max_callback);
                    break;
                case TRIANGLE:
                    _update_triangle(min_callback, max_callback);
                    break;
                case SQUARE:
                    _update_square(min_callback, max_callback);
                    break; 
            }
        } else {
            _callbacks_invalidated = false;
        }

        // Store current values for the next update
        _last_update = current_time;
        _last_normalised_progress = _calculate_normalised_progress();
    }
}

void Cycler::_update_sin(void (*min_callback)()=NULL, void (*max_callback)()=NULL) {

}
// void Cycler::_update_sawtooth(void (*min_callback)()=NULL, void (*max_callback)()=NULL);
void Cycler::_update_triangle(void (*min_callback)()=NULL, void (*max_callback)()=NULL) {

}

void Cycler::_update_square(void (*min_callback)()=NULL, void (*max_callback)()=NULL) {
    // If the normalised progress has decreased, then the period has reset so we hit a max
    if (max_callback != NULL) {
        float current_normalised_progress = _calculate_normalised_progress();
        if (current_normalised_progress < _last_normalised_progress) {
            max_callback();
        }
    }

    // If the normalised progress has gone from less than to greater than the duty we hit a min
    if (min_callback != NULL) {
        float current_normalised_progress = _calculate_normalised_progress();
        if (_last_normalised_progress < _duty && current_normalised_progress > _duty) {
            max_callback();
        }
    }
}