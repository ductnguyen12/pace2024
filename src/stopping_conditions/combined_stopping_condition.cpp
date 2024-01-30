#include <stopping_conditions/combined_stopping_condition.h>

CombinedStoppingCondition::CombinedStoppingCondition() {

}

CombinedStoppingCondition::CombinedStoppingCondition(std::initializer_list<StoppingCondition*> stoppingConditions) : stoppingConditions(stoppingConditions) {

}

bool CombinedStoppingCondition::canContinue() {
    for (StoppingCondition* stoppingCondition : stoppingConditions) {
        if (stoppingCondition->canContinue() == false) return false;
    }
    return true;
}

void CombinedStoppingCondition::notifyStarted() {
    for (StoppingCondition* stoppingCondition : stoppingConditions) {
        stoppingCondition->notifyStarted();
    }
}

void CombinedStoppingCondition::notifyIterated() {
    for (StoppingCondition* stoppingCondition : stoppingConditions) {
        stoppingCondition->notifyIterated();
    }
}

void CombinedStoppingCondition::addCondition(StoppingCondition* stoppingCondition) {
    stoppingConditions.push_back(stoppingCondition);
}

float CombinedStoppingCondition::getProgress() {
    float finalProgress = 0;
    for (StoppingCondition* stoppingConditions : stoppingConditions) {
        float newProgress = stoppingConditions->getProgress();
        if (newProgress > finalProgress) {
            finalProgress = newProgress;
        }
    }
    return finalProgress;
}

CombinedStoppingCondition::~CombinedStoppingCondition() {
    for (StoppingCondition* stoppingCondition : stoppingConditions) {
        delete stoppingCondition;
    }
}