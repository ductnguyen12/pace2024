#include <algorithms/brute_force.h>
#include <utils/utility.h>
#include <algorithm>
#include <iostream> 
#include <limits.h>

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

BruteForceAlgorithm::BruteForceAlgorithm() {

}

Solution BruteForceAlgorithm::findSolution(BipartiteGraph *graph, StoppingCondition* stoppingCondition) {
    stoppingCondition->notifyStarted();
    std::vector<int> order;
    std::vector<int> *solution = nullptr;
    unsigned long long minCrossing = UINT_MAX;
    
    if (graph != nullptr) {
        const std::vector<std::vector<int>>& vs = graph->getVs1();
        for (int i = 0; i < vs.size(); ++i) order.push_back(i);
        minCrossing = graph->count(order);
        solution = new std::vector<int>(order);
        int i = 0;
        while (stoppingCondition->canContinue() && next(order)) {
            stoppingCondition->notifyIterated();
            int crossing = graph->count(order);
            if (crossing < minCrossing) {
                minCrossing = crossing;
                delete solution;
                solution = new std::vector<int>(order);
            }
        }
    }
    return { minCrossing, solution };
}