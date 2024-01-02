#include <stopping_conditions/time_stopping_condition.h>
#include <assert.h>

TimeStoppingCondition::TimeStoppingCondition(unsigned int const microseconds) : duration(microseconds) { 
    
}

bool TimeStoppingCondition::canContinue() {
    assert(startTime.time_since_epoch().count() != 0);

    return std::chrono::steady_clock::now() - startTime < duration;
}

void TimeStoppingCondition::notifyStarted() {
    startTime = std::chrono::steady_clock::now();
}

void TimeStoppingCondition::notifyIterated() { 
    
}