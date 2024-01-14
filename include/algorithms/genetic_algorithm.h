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
    static std::pair<int, int> mutate(std::list<int>& list);

public:
    GeneticAlgorithm(StoppingCondition& stoppingCondition, int populationSize=50, double mutationRatio=0.1);

    Solution findSolution(BipartiteGraph *graph) override;
};
#endif