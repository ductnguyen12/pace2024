#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <algorithms/solution.h>
#include <stopping_conditions/stopping_condition.h>

class Algorithm {
protected:
    StoppingCondition& stoppingCondition;
public:
    Algorithm(StoppingCondition& stoppingCondition) : stoppingCondition(stoppingCondition) {};
    virtual Solution findSolution() = 0;

    bool canContinue() const {
        return stoppingCondition.canContinue();
    }
};

#endif