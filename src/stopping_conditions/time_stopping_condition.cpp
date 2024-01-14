#include <stopping_conditions/time_stopping_condition.h>

TimeStoppingCondition::TimeStoppingCondition(unsigned int const milliseconds) : duration(milliseconds * 1000) {
    
}

bool TimeStoppingCondition::canContinue() {
    return (std::chrono::steady_clock::now() - startTime) < duration;
}

void TimeStoppingCondition::notifyStarted() {
    startTime = std::chrono::steady_clock::now();
}

void TimeStoppingCondition::notifyIterated() { 
    
}