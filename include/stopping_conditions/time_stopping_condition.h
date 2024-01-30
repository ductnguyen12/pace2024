#ifndef TIME_STOPPING_CONDITION_H
#define TIME_STOPPING_CONDITION_H

#include <stopping_conditions/stopping_condition.h>
#include <chrono>

class TimeStoppingCondition : public StoppingCondition {
private:
    std::chrono::steady_clock::time_point startTime;
    std::chrono::microseconds duration;
public:
    TimeStoppingCondition(unsigned int const milliseconds);
    bool canContinue() override;
    void notifyStarted() override;
    void notifyIterated() override;
    float getProgress() override;
    [[nodiscard]] std::chrono::microseconds const& getDuration() const;
};

#endif