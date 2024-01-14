#include "algorithms/random_search.h"

#include <algorithm>
#include <random>
#include <vector>

#include<iostream>

#include<chrono>

 std::vector<int> RandomSearchAlgorithm::generateRandomOrdering(int n1){
    std::vector<int>v;
    for(int i=0;i<n1;++i) v.push_back(i);
    std::shuffle(v.begin(),v.end(), std::mt19937(std::random_device()()));
    return v;
}

RandomSearchAlgorithm::RandomSearchAlgorithm(StoppingCondition &stoppingCondition): Algorithm(stoppingCondition) {}

Solution RandomSearchAlgorithm::findSolution(BipartiteGraph *graph) {
    stoppingCondition.notifyStarted();
    std::vector<int>order;
    std::vector<int>* solution= nullptr;
    int minCross = -1;
    if(graph != nullptr){
        int n1 = graph->getN1();
        order = generateRandomOrdering(n1);
        minCross = graph->count(order);
        solution = new std::vector<int>(order);
        while(stoppingCondition.canContinue()){
            stoppingCondition.notifyIterated();
            order = generateRandomOrdering(n1);
            int crossing = graph->count(order);
            if(crossing < minCross){
                minCross = crossing;
                delete solution;
                solution = new std::vector<int>(order);
            }
        }

    }

    std::cout << "Started at: " << std::chrono::steady_clock::now().time_since_epoch().count() << std::endl;
    return {minCross,solution};
}
