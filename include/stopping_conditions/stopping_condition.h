#ifndef STOPPING_CONDITION_H
#define STOPPING_CONDITION_H

class StoppingCondition {
public:
    virtual bool canContinue() = 0;
    virtual void notifyStarted() = 0;
    virtual void notifyIterated() = 0;
};

/**
 * @brief DUMMY STOPPING CONDITION
 * This is a dummy stopping condition, canContinue() will always be true 
*/

class DummyStoppingCondition : public StoppingCondition {
public:
    bool canContinue() override { return true; }
    void notifyStarted() override { }
    void notifyIterated() override { }
};

#endif