#include "algorithms/simulated_annealing.h"

#include <algorithm>
#include <utils/random.h>
#include <utils/utility.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>

SimulatedAnnealing::SimulatedAnnealing() {}


std::pair<std::vector<int>, long long> SimulatedAnnealing::pickRandomNeighbor(BipartiteGraph* graph, std::pair<std::vector<int>, long long> &record, StoppingCondition* stoppingCondition) {
    Random& random = Random::getInstance();
    std::vector<int>& order = record.first;
    int n1 = order.size();
    double coef = 1;
#if defined(JUMP)
#pragma message("Jump")
    coef -= stoppingCondition->getProgress();
#endif
    int newIndex,oldIndex;
    newIndex = oldIndex = 0;
    while(newIndex == oldIndex){
        oldIndex = random.getInt(0, n1);
        int randomJump = random.getInt(0, ceil(n1 * coef)) + 1;
        int val = random.getInt(0,2) ;
        val == 0 ? randomJump*=-1 : randomJump*=1;
#ifdef DEBUG_MODE
        std::cout<<randomJump<<' ';
#endif
        newIndex = oldIndex + randomJump;
        if(newIndex < 0) newIndex = 0;
        if(newIndex > n1-1) newIndex = n1-1;
    }
    std::vector neighbor(order);
    long long newCount = record.second - shiftPartialOrder(*graph, neighbor.begin() + newIndex, neighbor.begin() + oldIndex, random.randOutcome(0.5f));
    return std::make_pair(std::move(neighbor), newCount);
}

float SimulatedAnnealing::acceptanceProbability(long long oldFitness, long long curFitness, float t) {
    if(curFitness < oldFitness){
        return 1.0;
    }
    return std::exp( (oldFitness - curFitness) / t);
}


Solution SimulatedAnnealing::findSolution(BipartiteGraph *graph, StoppingCondition* stoppingCondition) {
    Random& random = Random::getInstance();
    stoppingCondition->notifyStarted();
    std::vector<int>order;
    std::vector<int>* solution= nullptr;
    long long minCross = -1;
    int steps = 0;
    double t=0.01;
    if(graph != nullptr) {
#if defined(BARY) || defined(JUMP)
#pragma message("Bary or Jump")
        order = applyBarycentricHeuristic(graph);
#elif defined(MEDIAN)
#pragma message("Median")
        order = applyMedianHeuristic(graph);
#else 
#pragma message("Random")
        order = getRandomOrder(graph);
#endif
        
        minCross = graph->count(order);
        solution = new std::vector(order);
        std::pair<std::vector<int>, long long> current = std::make_pair(order, minCross);
        while(stoppingCondition->canContinue()){
            stoppingCondition->notifyIterated();
            ++steps;
            std::pair<std::vector<int>, long long> neighbor = pickRandomNeighbor(graph, current, stoppingCondition);
            if(random.randOutcome(acceptanceProbability(current.second, neighbor.second, t))){
                if(neighbor.second < minCross){
                    minCross = neighbor.second;
                    solution->assign(neighbor.first.begin(), neighbor.first.end());
                }
                current = std::make_pair(std::move(neighbor.first), neighbor.second);
            }
            t = t / (1.0 + std::log(1.0 + steps));
        }
    }
#ifdef DEBUG_MODE
    std::cout << "Finished at: " << std::chrono::steady_clock::now().time_since_epoch().count() << std::endl;
#endif
    return {minCross, solution};
}