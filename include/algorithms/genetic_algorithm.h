#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <list>

class GeneticAlgorithm : public Algorihm {
private:
    /**
     * @brief Mutate an order of elements and return the affected positions
    */
    static std::list<int> mutate(std::list<int>& list);
    static std::list<int> generate(int size);
public:
    GeneticAlgorithm(StoppingCondition& stoppingCondition, int populationSize = 50, double mutationRatio=0.1, double crossoverRation=0.1);

    Solution findSolution(BipartiteGraph *graph) override;
};
#endif