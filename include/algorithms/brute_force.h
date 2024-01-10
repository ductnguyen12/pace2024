#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <vector>
#include <algorithms/algorithm.h>
#include <graph/bipartite_graph.h>


class BruteForceAlgorithm : public Algorithm {
private:
    static bool next(std::vector<int> &v);
public:
    BruteForceAlgorithm(StoppingCondition& stoppingCondition);

    /**
     * @brief Finds the minimal crossing edges by trying all permutations of orders of the
     * second layer
     * @return A solution with the minimum number of crossing edges and a corresponding
     * ordered list of vertices
     * @note If there are no solution (`stoppingCondition.stoppingCondition` is false) 
     * then the `Solution::minCrossing` is -1 and `Solution::order` is `nullptr`.
    */
    Solution findSolution(BipartiteGraph *graph) override;
};

#endif