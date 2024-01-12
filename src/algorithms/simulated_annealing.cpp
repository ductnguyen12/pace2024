#include "algorithms/simulated_annealing.h"

#include <algorithm>
#include <random>
#include <vector>
#include<iostream>
#include <cmath>
#include <chrono>

SimulatedAnnealing::SimulatedAnnealing(StoppingCondition &stoppingCondition) : Algorithm(stoppingCondition){}

std::vector<int> SimulatedAnnealing::generateRandomStart(int n1) {
    std::vector<int>v;
    for(int i=0;i<n1;++i) v.push_back(i);
    std::shuffle(v.begin(),v.end(), std::mt19937(std::random_device()()));
    return v;
}

std::vector<int> SimulatedAnnealing::pickRandomNeighbor(std::vector<int> &v) {
    int n1 = v.size();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> indexDistribution(0, n1 - 1);
    std::uniform_int_distribution<int> jumpDistribution(- (n1 - 1), n1 - 1);

    int newIndex,oldIndex;
    newIndex = oldIndex = 0;
    while(newIndex == oldIndex){
        oldIndex = indexDistribution(gen);
        int randomJump = jumpDistribution(gen);
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

double SimulatedAnnealing::acceptanceProbability(int oldFitness, int curFitness, double t) {
    if(curFitness < oldFitness){
        return 1.0;
    }
    return std::exp( (oldFitness - curFitness) / t);
}


Solution SimulatedAnnealing::findSolution(BipartiteGraph *graph) {
    stoppingCondition.notifyStarted();
    std::vector<int>order;
    std::vector<int>* solution= nullptr;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    int minCross = -1;
    int steps = 0;
    double t=0.01;
    if(graph != nullptr) {
        int n1 = graph->getN1();
        order = generateRandomStart(n1);
        minCross = graph->count(order);
        solution = new std::vector(order);
        std::pair<std::vector<int>,int> cur = std::make_pair(order,minCross);
        while(stoppingCondition.canContinue()){
            stoppingCondition.notifyIterated();
            ++steps;
            order = pickRandomNeighbor(cur.first);
            int crossing = graph->count(order);
            if(acceptanceProbability(cur.second,crossing,t) > distribution(gen)){
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

    std::cout << "Finished at: " << std::chrono::steady_clock::now().time_since_epoch().count() << std::endl;
    return {minCross,solution};
}