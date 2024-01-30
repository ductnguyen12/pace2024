#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <vector>
#include <algorithms/algorithm.h>
#include <graph/bipartite_graph.h>

class SimulatedAnnealing : public Algorithm {
private:
    static std::vector<int> generateRandomStart(int n1);
    static std::vector<int> pickRandomNeighbor(std::vector<int> &v);
    static float acceptanceProbability(int oldFitness,int curFitness,float t);
public:
    SimulatedAnnealing();

    /**
     * @brief generate random permutations and saves the permutation with minimal crossing number
     * @return A solution with the minimum number of crossing found over the search
    */
    Solution findSolution(BipartiteGraph *graph, StoppingCondition* StoppingCondition) override;
};

#endif //SIMULATED_ANNEALING_H
