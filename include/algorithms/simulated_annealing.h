#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <vector>
#include <algorithms/algorithm.h>
#include <graph/bipartite_graph.h>

class SimulatedAnnealing : public Algorithm {
private:
    static std::vector<int> generateRandomStart(int n1);
    static std::pair<std::vector<int>, unsigned long long> pickRandomNeighbor(BipartiteGraph* graph, std::pair<std::vector<int>, unsigned long long> &record, StoppingCondition* stoppingCondition);
    static float acceptanceProbability(unsigned long long oldFitness,unsigned long long curFitness,float t);
public:
    SimulatedAnnealing();

    /**
     * @brief generate random permutations and saves the permutation with minimal crossing number
     * @return A solution with the minimum number of crossing found over the search
    */
    Solution findSolution(BipartiteGraph *graph, StoppingCondition* StoppingCondition) override;
};

#endif //SIMULATED_ANNEALING_H
