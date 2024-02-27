#include "algorithms/random_search.h"

#include <algorithm>
#include <vector>

#include <iostream>
#include <utils/utility.h>
#include <utils/random.h>
#include <chrono>
#include <limits.h>

 std::vector<int> RandomSearchAlgorithm::generateRandomOrdering(int n1){
    Random& random = Random::getInstance();
    std::vector<int> v = generateVector(n1);
    random.shuffle(v);
    return v;
}

RandomSearchAlgorithm::RandomSearchAlgorithm() {}

Solution RandomSearchAlgorithm::findSolution(BipartiteGraph *graph, StoppingCondition* stoppingCondition) {
    stoppingCondition->notifyStarted();
    std::vector<int>order;
    std::vector<int>* solution= nullptr;
    unsigned long long minCross = UINT_MAX;
    if(graph != nullptr){
        int n1 = graph->getN1();
        order = generateRandomOrdering(n1);
        minCross = graph->count(order);
        solution = new std::vector<int>(order);
        while(stoppingCondition->canContinue()){
            stoppingCondition->notifyIterated();
            order = generateRandomOrdering(n1);
            unsigned long long crossing = graph->count(order);
            if(crossing < minCross){
                minCross = crossing;
                solution->assign(order.begin(), order.end());
            }
        }

    }
    return {minCross, solution};
}
