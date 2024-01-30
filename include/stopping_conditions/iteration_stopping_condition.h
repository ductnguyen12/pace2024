#ifndef ITERATION_STOPPING_CONDITION_H
#define ITERATION_STOPPING_CONDITION_H

#include <stopping_conditions/stopping_condition.h>
#include <chrono>

class IterationStoppingCondition : public StoppingCondition {
private:
    int count, max;
public:
    IterationStoppingCondition(unsigned int max);
    bool canContinue() override;
    void notifyStarted() override;
    void notifyIterated() override;
    float getProgress() override;
};

#endif