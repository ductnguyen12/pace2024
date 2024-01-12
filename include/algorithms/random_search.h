#ifndef RANDOM_SEARCH_H
#define RANDOM_SEARCH_H

#include <vector>
#include <algorithms/algorithm.h>
#include <graph/bipartite_graph.h>

class RandomSearchAlgorithm : public Algorithm {
private:
    static std::vector<int> generateRandomOrdering(int n1);
public:
    RandomSearchAlgorithm(StoppingCondition& stoppingCondition);

    /**
     * @brief generate random permutations and saves the permutation with minimal crossing number
     * @return A solution with the minimum number of crossing found over the search
    */
    Solution findSolution(BipartiteGraph *graph) override;
};

#endif //RANDOM_SEARCH_H
