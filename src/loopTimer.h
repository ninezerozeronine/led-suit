// Convenience class to see how fast the loop function is

#ifndef looptimer_h
#define looptimer_h

#include <Arduino.h>

class LoopTimer {
    public:
        LoopTimer();
        LoopTimer(int _loops_to_count);
        void update();
        float get_loop_time();

    private:
        // The number of loops to count to get an average loop time
        int loops_to_count;

        // How many loops have been counted
        int num_loops;
  
        // Time at the last loop count
        unsigned int last_count_millis;

        // Average time of a loop
        float loop_time;

        void constructor_defaults();
};

#endif