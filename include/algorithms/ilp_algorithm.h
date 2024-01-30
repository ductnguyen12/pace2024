//
// Created by ducnt on 1/29/24.
//

#ifndef ILP_ALGORITHM_H
#define ILP_ALGORITHM_H


#include <algorithms/algorithm.h>

class ILPAlgorithm : public Algorithm {
public:
    ILPAlgorithm();

    Solution findSolution(BipartiteGraph *graph, StoppingCondition *stoppingCondition) override;
};


#endif //ILP_ALGORITHM_H
