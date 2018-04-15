// Class to handle values that cycle over time

class Cycler {
    public:
        enum cycle_t {
            STATIC,
            SIN,
            SAWTOOTH,
            TRIANGLE,
            SQUARE
        };
        Cycler();
        void init();
        void set_cycle_type(cycle_t cycle_type);
        float get_value();
        void update();
        void set_min(float min);
        void set_max(float max);
        void set_speed(float speed);
        void set_period(unsigned long period)

    private:
        // How far to progress per millisecond
        float _speed

        // The current value of the cycler
        float _value;

        // The max value of the cycler
        float _max;

        // The min value of the cycler
        float _min;

        // The current mode
        mode_t _mode;

        // When the cycler was last updated
        unsigned long _last_update;

        // Update various modes
        void _update_sin();
        void _update_sawtooth();
        void _update_triangle();
        void _update_square();

    public:
        Cycler() {
            _value_timebase_speed = 0.1;
            _value_timebase = 0;
            _hue_speed = 0.1;
            _hue = 0;
            _hue_offset = 0;
            _mode = STATIC;
            _speed_mult = 1.0;
        }

        void init() {
            _last_update = millis();
        }

        float wrap_255_float(float input) {
            // Do a floating point modulo 0-255.999999...
            int int_part = int(input);
            float decimal_part = input - int_part;
            int wrapped = int_part % 256;
            float wrapped_float = wrapped + decimal_part;

            return wrapped_float;
        }

        void set_mode(mode_t mode) {
            _mode = mode;
        }

        uint8_t get_hue() {
            return (uint8_t(_hue) + _hue_offset) % 256;
        }

        void set_hue(float hue) {
            _hue = hue;
        }

        void set_hue_speed(float speed) {
            _hue_speed = speed;
        }

        void set_hue_offset(uint8_t hue_offset) {
            _hue_offset = hue_offset;
        }

        uint8_t get_value() {
            return sin8(uint8_t(_value_timebase));
        }

        void set_value_timebase_speed(float speed) {
            _value_timebase_speed = speed;
        }

        void set_value_timebase(float value_timebase) {
            _value_timebase = wrap_255_float(value_timebase);
        }

        void update() {
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
                        update_static(elapsed_millis);
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

        void update_static(uint8_t elapsed_millis) {
            // Nothing to do!
        }

        void update_cycle_hue(uint8_t elapsed_millis) {
            float new_hue = _hue + (elapsed_millis * _hue_speed * _speed_mult);
            _hue = wrap_255_float(new_hue);
        }

        void update_pulse_value(uint8_t elapsed_millis) {
            float new_value_timebase = _value_timebase + (elapsed_millis * _value_timebase_speed * _speed_mult);
            _value_timebase = wrap_255_float(new_value_timebase);
        }

        void update_pulse_value_change_hue(uint8_t elapsed_millis) {
            uint8_t _previous_value = get_value();
            update_pulse_value(elapsed_millis);
            // When it goes from above the threshold to below it
            if ((_previous_value >= HUE_CHANGE_THRESHOLD) && (get_value() < HUE_CHANGE_THRESHOLD)) {
                _hue = float(random8());
            }
        }
        void update_pulse_value_cycle_hue(uint8_t elapsed_millis) {
            update_pulse_value(elapsed_millis);
            update_cycle_hue(elapsed_millis);
        }
};