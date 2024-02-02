#include "algorithms/simulated_annealing.h"

#include <algorithm>
#include <utils/random.h>
#include <utils/utility.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <chrono>

SimulatedAnnealing::SimulatedAnnealing() {}


std::vector<int> SimulatedAnnealing::pickRandomNeighbor(std::vector<int> &v, StoppingCondition* stoppingCondition) {
    Random& random = Random::getInstance();
    int n1 = v.size();
    double coef = 1;
#ifdef JUMP
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
    std::vector<int>ret;
    if(newIndex > oldIndex){
        for(int i=0;i<=newIndex;++i){
            if(i==oldIndex) continue;
            ret.push_back(v[i]);
        }
        ret.push_back(v[oldIndex]);
        for(int i=newIndex+1;i<n1;++i){
            ret.push_back(v[i]);
        }
    }else{
        for(int i=0;i<newIndex;++i){
            ret.push_back(v[i]);
        }
        ret.push_back(v[oldIndex]);
        for(int i=newIndex;i<n1;++i){
            if(i==oldIndex) continue;
            ret.push_back(v[i]);
        }
    }
    return ret;
}

float SimulatedAnnealing::acceptanceProbability(int oldFitness, int curFitness, float t) {
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
    int minCross = -1;
    int steps = 0;
    double t=0.01;
    if(graph != nullptr) {
#if defined(BARY) || defined(JUMP)
#pragma message("Bary or Jump")
        order = applyBarycentricHeuristic(graph);
#elif defined(MEDIUM)
#pragma message("Medium")
        order = applyMediumHeuristic(graph);
#else 
#pragma message("Random")
        order = applyRandom(graph);
#endif
        
        minCross = graph->count(order);
        solution = new std::vector(order);
        std::pair<std::vector<int>,int> cur = std::make_pair(order,minCross);
        while(stoppingCondition->canContinue()){
            stoppingCondition->notifyIterated();
            ++steps;
            order = pickRandomNeighbor(cur.first, stoppingCondition);
            int crossing = graph->count(order);
            if(random.randOutcome(acceptanceProbability(cur.second,crossing,t))){
                if(crossing < minCross){
                    minCross = crossing;
                    delete solution;
                    solution = new std::vector(order);
                }
                cur = std::make_pair(order,crossing);
            }
            t = t / (1.0 + std::log(1.0 + steps));
        }
    }
#ifdef DEBUG_MODE
    std::cout << "Finished at: " << std::chrono::steady_clock::now().time_since_epoch().count() << std::endl;
#endif
    return {minCross,solution};
}