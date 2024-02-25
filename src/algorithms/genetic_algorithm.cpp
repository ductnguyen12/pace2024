#include <algorithms/genetic_algorithm.h>
#include <utils/utility.h>
#include <utils/random.h>
#include <algorithm>
#include <iostream>
#ifdef DEBUG_MODE 
#endif

GeneticAlgorithm::GeneticAlgorithm(int populationSize, double mutationRatio) : populationSize(populationSize), mutationRatio(mutationRatio){
    
}

long long GeneticAlgorithm::mutate(BipartiteGraph* graph, std::vector<int>& order) {
    Random& random = Random::getInstance();
    int first = random.getInt(order.size());
    auto firstIter = std::next(order.begin(), first);
    int value = *firstIter;
    int second = random.getInt(order.size());
    auto secondIter = std::next(order.begin(), second);
    bool right = random.randOutcome(0.5f);
    return shiftPartialOrder(*graph, firstIter, secondIter, right);
}

auto crossingComparator = [](auto const& a, auto const& b) {
    return a.second < b.second;
};

Solution GeneticAlgorithm::findSolution(BipartiteGraph *graph, StoppingCondition* stoppingCondition) {
    stoppingCondition->notifyStarted();
    long long minCrossing = -1;
    std::vector<int> *order = nullptr;
    if (graph != nullptr) {
        Random& random = Random::getInstance();
        std::vector<std::pair<std::vector<int>, long long>> population;
#if defined(BARY)
        std::vector<int> first_vector = applyBarycentricHeuristic(graph);
#elif defined(MEDIAN)
        std::vector<int> first_vector = applyMedianHeuristic(graph);
#else
        std::vector<int> first_vector = getRandomOrder(graph);
#endif
        population.emplace_back(std::move(first_vector), graph->count(first_vector));
        for (int i = 1; i < populationSize && stoppingCondition->canContinue(); i++) {
            std::vector<int> order = getRandomOrder(graph);
            population.emplace_back(std::move(order), graph->count(order));
        }
        auto sort = [&population]() { std::sort(population.begin(), population.end(), crossingComparator); };
        sort();
        while (stoppingCondition->canContinue()) {
            for (int i = 0; i < populationSize && stoppingCondition->canContinue(); i++) {
                stoppingCondition->notifyIterated();
                std::vector<int>& order = population[i].first;
                long long& count = population[i].second;
                if (random.randOutcome(mutationRatio)) {
                    std::vector<int> mutant(order);
                    long long delta = mutate(graph, mutant);
                    population.push_back(std::make_pair(std::move(mutant), count - delta));
                }
            }
            sort();
            population.resize(populationSize);
        }
        order = new std::vector<int>(population[0].first.begin(), population[0].first.end());
        minCrossing = population[0].second;
    }
    return { minCrossing, order };
}