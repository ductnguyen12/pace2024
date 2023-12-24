#include <algorithms/brute_force.h>
#include <utils/utility.h>
#include <algorithm>
#include <iostream> 

bool BruteForceAlgorithm::next(std::vector<int> &v) {    
    for (int idx = v.size() - 2; idx >= 0; idx--) {
        if (v[idx] < v[idx + 1]) {
            int idx2 = idx + 1;
            for (; idx2 < v.size() - 1; idx2++) 
                if (v[idx2 + 1] < v[idx]) break;
            swap(v[idx], v[idx2]);
            std::sort(v.begin() + idx + 1, v.end());
            return true;            
        }
    }
    return false;
}

BruteForceAlgorithm::BruteForceAlgorithm(StoppingCondition& stoppingCondition, BipartiteGraph& graph) : Algorithm(stoppingCondition), graph(graph) {

}

Solution BruteForceAlgorithm::findSolution() {
    const std::vector<std::vector<int>>& vs = graph.getVs1();
    std::vector<int> order;
    std::vector<int> *solution = nullptr;
    for (int i = 0; i < vs.size(); ++i) order.push_back(i);
    int minCrossing = graph.count(order);
    int i = 0;
    while (next(order)) {
        int crossing = graph.count(order);
        if (crossing < minCrossing) {
            minCrossing = crossing;
            solution = new std::vector<int>(order);
        }
    }
    return { minCrossing, solution };
}