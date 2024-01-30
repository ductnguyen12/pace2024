#include <algorithms/genetic_algorithm.h>
#include <utils/utility.h>
#include <utils/random.h>
#include <algorithm>
#ifdef DEBUG_MODE 
#include <iostream>
#endif

GeneticAlgorithm::GeneticAlgorithm(int populationSize, double mutationRatio) : populationSize(populationSize), mutationRatio(mutationRatio){
    
}

std::pair<int, int> GeneticAlgorithm::mutate(std::list<int>& list) {
    Random& random = Random::getInstance();
    int first = random.getInt(list.size());
    auto firstIter = std::next(list.begin(), first);
    int value = *firstIter;
    int second = random.getInt(list.size());
    auto secondIter = std::next(list.begin(), second);
    list.erase(firstIter);
    list.insert(secondIter, value);
    return std::make_pair(first, second);
}

auto crossingComparator = [](auto const& a, auto const& b) {
    return a.second < b.second;
};

Solution GeneticAlgorithm::findSolution(BipartiteGraph *graph, StoppingCondition* stoppingCondition) {
    stoppingCondition->notifyStarted();
    int minCrossing = -1;
    std::vector<int> *order = nullptr;
    if (graph != nullptr) {
        Random& random = Random::getInstance();
        std::vector<std::pair<std::list<int>, int>> population;
        for (int i = 0; i < populationSize; i++) {
            std::list<int> order = generateList(graph->getN1());
            population.emplace_back(std::move(order), graph->count(order));
        }
        auto sort = [&population]() { std::sort(population.begin(), population.end(), crossingComparator); };
        sort();
        while (stoppingCondition->canContinue()) {
            for (int i = 0; i < populationSize && stoppingCondition->canContinue(); i++) {
                stoppingCondition->notifyIterated();
                if (random.randOutcome(mutationRatio)) {
                    std::list<int> mutant(population[i].first);
                    random.shuffle(mutant);
                    population.push_back(std::make_pair(mutant, graph->count(mutant)));
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