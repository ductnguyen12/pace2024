#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <algorithms/solution.h>
#include <graph/bipartite_graph.h>
#include <stopping_conditions/stopping_condition.h>

class Algorithm {
protected:
    StoppingCondition& stoppingCondition;
public:
    Algorithm(StoppingCondition& stoppingCondition) : stoppingCondition(stoppingCondition) {};

    /**
     * @brief Finds and returns a solution
     * @return solution
     * @note This pure virtual function is intended to be implemented in derived classes
     * to search for and return a solution based on specific algorithms. Also, remember to call
     * `stoppingCondition.notifySearch()` to initialize the stopping condition properly.
    */
    virtual Solution findSolution(BipartiteGraph *graph) = 0;

    /**
     * @brief Checks if the algorithm can continue based on the stopping condition
     * @return true if the algorithm can continue
    */
    bool canContinue() const {
        return stoppingCondition.canContinue();
    }
};

#endif