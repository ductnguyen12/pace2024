#ifndef COMBINED_STOPPING_CONDITION_H
#define COMBINED_STOPPING_CONDITION_H

#include <initializer_list>
#include <stopping_conditions/stopping_condition.h>
#include <stopping_conditions/time_stopping_condition.h>
#include <vector>

class CombinedStoppingCondition : public StoppingCondition {
private:
    std::vector<StoppingCondition*> stoppingConditions;

public:
    CombinedStoppingCondition();
    CombinedStoppingCondition(std::initializer_list<StoppingCondition*> stoppingConditions);
    bool canContinue() override;
    void notifyStarted() override;
    void notifyIterated() override;
    void addCondition(StoppingCondition* stoppingCondition);
    float getProgress() override;
    ~CombinedStoppingCondition();

    operator TimeStoppingCondition*() const;
};

#endif