#ifndef STOPPING_CONDITION_H
#define STOPPING_CONDITION_H

class StoppingCondition {
public:
    virtual bool canContinue() = 0;
    virtual void notifyStarted() { };
    virtual void notifyIterated() { };
    virtual float getProgress() = 0;
};

/**
 * @brief A dummy stopping condition, canContinue() will always be true 
*/

class DummyStoppingCondition : public StoppingCondition {
public:
    bool canContinue() override { return true; }
};

#endif