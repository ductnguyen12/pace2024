//
// Created by ducnt on 1/29/24.
//

#ifndef ILP_ALGORITHM_H
#define ILP_ALGORITHM_H


#include <algorithms/algorithm.h>

class ILPAlgorithm : public Algorithm {
private:
    std::chrono::microseconds const* duration = nullptr;
public:
    ILPAlgorithm(StoppingCondition &stoppingCondition);

    Solution findSolution(BipartiteGraph *graph) override;
};


#endif //ILP_ALGORITHM_H
