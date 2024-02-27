
#ifndef SIMPLE_TIMER_H
#define SIMPLE_TIMER_H

#include <chrono>

class SimpleTimer {
private:
    std::chrono::steady_clock::time_point point = std::chrono::steady_clock::now();
public:
    void start() {
        point = std::chrono::steady_clock::now();
    }
    int count() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - point).count();
    }
};

#endif