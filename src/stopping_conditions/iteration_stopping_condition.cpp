#include <stopping_conditions/iteration_stopping_condition.h>

IterationStoppingCondition::IterationStoppingCondition(unsigned int max) : max(max) {

}

bool IterationStoppingCondition::canContinue() {
    return count <= max;
}

void IterationStoppingCondition::notifyStarted() {
    count = 0;
}

void IterationStoppingCondition::notifyIterated() {
    count += 1;
}

float IterationStoppingCondition::getProgress() {
    return (float) count / max;
}