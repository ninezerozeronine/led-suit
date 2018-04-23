// Class to handle values that cycle over time
#include "cycler.h"

// Constructor
Cycler::Cycler(
            uint16_t period,
            float min,
            float max,
            mode_t cycle_mode,
            float duty
) {
    if (period < 1) {
        period = 1;
    }
    _period = _target_period = period;
    _min = min;
    _max = max;
    _value = min;
    _cycle_mode = cycle_mode;
    _duty = duty;
    _last_update_time = 0;
    _last_gradual_time = 0;
    _offset = _target_offset = 0;
    _last_normalised_progress = 0.0;
    _callbacks_invalidated = false;
}


// Initialise the object
//
// Call this outside the constructor so caller has control when it runs
void Cycler::init() {
    _last_update_time = millis();
    _last_normalised_progress = _calculate_normalised_progress();
}


void Cycler::set_cycle_mode(mode_t cycle_mode) {
    _cycle_mode = cycle_mode;
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
    if (duty < 0) {
        duty = 0.0;
    }
    if (duty > 1) {
        duty = 1.0;
    }
    _duty = duty;
    _callbacks_invalidated = true;
}

//
void Cycler::set_offset(uint16_t offset) {
    _offset = offset;
    _callbacks_invalidated = true;
}

void Cycler::set_target_offset(uint16_t target_offset) {
    _target_offset = target_offset;
}

uint16_t Cycler::get_period(){
    return _period;
}


// Set the period of the cycler
//
// maintain_progress means that the value of the cycler wont change. This
// is achieved by setting the offset appropriately
void Cycler::set_period(uint16_t period, bool maintain_progress) {
    if (period < 1) {
        period = 1;
    }

    if (maintain_progress) {
        // How far through the current period are we right now
        unsigned long current_time = millis();
        unsigned long cycler_time = current_time + _offset;
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

        set_offset(new_offset);
        set_target_offset(new_offset);
    }

    _period = period;
    _callbacks_invalidated = true;

    // if (maintain_progress && !gradual) {
    //     // How far through the current period are we right now
    //     unsigned long current_time = millis();
    //     unsigned long cycler_time = current_time + _offset;
    //     unsigned long old_period_time = cycler_time % _period;
    //     float period_progress = float(old_period_time)/float(_period);

    //     // Calculate offset to get us to the same point in the period
    //     unsigned long new_period_time = period * period_progress;
    //     unsigned long non_offset_new_period_time = current_time % period;
    //     long new_offset = new_period_time - non_offset_new_period_time;

    //     // Ensure offset is +ve
    //     if (new_offset < 0) {
    //         new_offset += period;
    //     }

    //     _offset = _target_offset = new_offset;
    //     _period = _target_period = period;
    //     _callbacks_invalidated = true;

    // } else if (gradual && !maintain_progress) {
    //     _target_period = period;

    // } else {
    //     _period = _target_period = period;
    //     _callbacks_invalidated = true;
    // }
}


void Cycler::set_target_period(uint16_t target_period) {
    _target_period = target_period;
}

// Get the current value of the cycler
float Cycler::get_value() {
    switch (_cycle_mode) {
        case STATIC:
            _value = _calculate_STATIC();
            break;
        case TRIG:
            _value = _calculate_TRIG();
            break;
        case TRIANGLE:
            _value = _calculate_TRIANGLE();
            break;
        case SQUARE:
            _value = _calculate_SQUARE();
            break;
    }
    return _value;
}


float Cycler::_calculate_STATIC() {
    return _value;
}


float Cycler::_calculate_TRIG() {
    // Progress through period
    float progress = _calculate_normalised_progress();

    // Add 1 to the progress to read the value for pi at progress = 0
    float radian_progress = (progress + 0.5) * 6.2831853;

    // Calsulate cosine
    float cosine = cos(radian_progress);

    // Make the value positive and range between 0 and 1
    float lerp_value = (cosine + 1.0) / 2.0;

    // Lerp the value
    float ret = ((1.0 - lerp_value) * _min) + (lerp_value * _max);
    return ret;
}


float Cycler::_calculate_TRIANGLE() {
    float ret;
    float progress = _calculate_normalised_progress();
    // Linearly interpolate beteen min and max based on how far between period
    // start and duty*period we currently are
    if (progress < _duty) {
        float rise_progress = progress / _duty;
        ret = ((1.0 - rise_progress) * _min) + (rise_progress * _max);

    // Linearly interpolate beteen max and min based on how far between duty*period
    // and the end of the period we currently are
    } else {
        float fall_progress = (progress - _duty) / (1.0 - _duty);
        ret = ((1.0 - fall_progress) * _max) + (fall_progress * _min);
    }
    return ret;
}


float Cycler::_calculate_SQUARE() {
    float progress = _calculate_normalised_progress();
    float val;
    if (progress < _duty) {
        val = _max;
    } else {
        val = _min;
    }
    return val;
}


uint16_t Cycler::_get_gradual_value(uint16_t current, uint16_t target, uint8_t rate, uint8_t timespan) {
    uint16_t ret = current;
    uint8_t amount = 5;//rate * timespan;

    if (target > current) {
        if (target - current > amount) {
            ret = current + amount;
        } else {
            ret = target;
        }
    } else {
        if (current - target > amount) {
            ret = current - amount;
        } else {
            ret = target;
        }
    }
    return ret;
}


void Cycler::_update_graduals() {
    // Get how long it's been since the last update of the graduals
    unsigned long current_time = millis();

    uint8_t gradual_interval = 10;
    uint8_t gradual_rate = 1;

    bool offset_not_reached = _target_offset != _offset;
    bool period_not_reached = _target_period != _period;

    if (offset_not_reached || period_not_reached) {
        uint8_t millis_since_last_grad = current_time - _last_gradual_time;
        if (millis_since_last_grad > gradual_interval) {
            if (offset_not_reached) {
                uint16_t new_offset = _get_gradual_value(
                    _offset, 
                    _target_offset,
                    gradual_rate,
                    millis_since_last_grad
                );
                set_offset(new_offset);
            }

            if (period_not_reached) {
                uint16_t new_period = _get_gradual_value(
                    _period, 
                    _target_period,
                    gradual_rate,
                    millis_since_last_grad
                );
                set_period(new_period, true);
            }
            _last_gradual_time = current_time;
        }
    }
}

// Call this once each time around the main arduino loop
//
// min and max callbacks are called when the value hits a max or a min.
void Cycler::update(void (*min_callback)(), void (*max_callback)()) {
    // Update the gradual offset and periods
    _update_graduals();

    // Get how long it's been since the last update
    unsigned long current_time = millis();
    
    // If measurable time has passed
    uint8_t elapsed_millis = current_time - _last_update_time;
    if (elapsed_millis > 0) {
        if (!_callbacks_invalidated) {
            // Update based on current mode
            switch (_cycle_mode) {
                case STATIC:
                    // Nothing to do!
                    break;
                case TRIG:
                    _update_TRIG(min_callback, max_callback);
                    break;
                case TRIANGLE:
                    _update_TRIANGLE(min_callback, max_callback);
                    break;
                case SQUARE:
                    _update_SQUARE(min_callback, max_callback);
                    break; 
            }
        } else {
            _callbacks_invalidated = false;
        }

        // Store current values for the next update
        _last_update_time = current_time;
        _last_normalised_progress = _calculate_normalised_progress();
    }
}


void Cycler::_update_TRIG(void (*min_callback)(), void (*max_callback)()) {
    // If the normalised progress has decreased, then the period has reset so we hit a min
    if (min_callback != NULL) {
        float current_normalised_progress = _calculate_normalised_progress();
        if (current_normalised_progress < _last_normalised_progress) {
            min_callback();
        }
    }

    // If the normalised progress has gone from less than to greater than halfway then we hit a max
    if (max_callback != NULL) {
        float current_normalised_progress = _calculate_normalised_progress();
        if ((_last_normalised_progress <= 0.5) && (current_normalised_progress > 0.5)) {
            max_callback();
        }
    }
}


void Cycler::_update_TRIANGLE(void (*min_callback)(), void (*max_callback)()) {
    // If the normalised progress has decreased, then the period has reset so we hit a min
    if (min_callback != NULL) {
        float current_normalised_progress = _calculate_normalised_progress();
        if (current_normalised_progress < _last_normalised_progress) {
            min_callback();
        }
    }

    // If the normalised progress has gone from less than to greater than the duty we hit a max
    if (max_callback != NULL) {
        float current_normalised_progress = _calculate_normalised_progress();
        if (_last_normalised_progress <= _duty && current_normalised_progress > _duty) {
            max_callback();
        }
    }
}


void Cycler::_update_SQUARE(void (*min_callback)(), void (*max_callback)()) {
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
        if (_last_normalised_progress <= _duty && current_normalised_progress > _duty) {
            min_callback();
        }
    }
}


float Cycler::_calculate_normalised_progress() {
        unsigned long current_time = millis();
        unsigned long cycler_time = current_time + _offset;
        unsigned long period_time = cycler_time % _period;
        float period_progress = float(period_time)/float(_period);
        return period_progress;
}