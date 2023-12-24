#ifndef BRUTE_FORCE_H
#define BRUTE_FORCE_H

#include <vector>
#include <algorithms/algorithm.h>
#include <graph/bipartite_graph.h>


class BruteForceAlgorithm : public Algorithm {
private:
    static bool next(std::vector<int> &v);
    BipartiteGraph& graph;
public:
    BruteForceAlgorithm(StoppingCondition& stoppingCondition, BipartiteGraph& graph);
    Solution findSolution() override;
};

#endif