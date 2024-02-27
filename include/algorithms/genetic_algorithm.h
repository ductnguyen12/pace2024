#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <algorithms/algorithm.h>
#include <list>

class GeneticAlgorithm : public Algorithm {
private:
    int populationSize;
    double mutationRatio;
    /**
     * @brief Mutate an order of elements and return the affected range.
    */
    static unsigned long long mutate(BipartiteGraph *graph, std::vector<int>& order);

public:
    GeneticAlgorithm(int populationSize=10, double mutationRatio=0.1);

    Solution findSolution(BipartiteGraph *graph, StoppingCondition* stoppingCondition) override;
};
#endif