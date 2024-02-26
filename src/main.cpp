#include <iostream>
#include <graph/bipartite_graph.h>
#include <algorithms/brute_force.h>
#include <utils/argument.h>
#include <problems/problem.h>
#include <utils/utility.h>
#include <utils/random.h>
#include <stopping_conditions/time_stopping_condition.h>
#include <algorithms/genetic_algorithm.h>
#include <vector>
#include <iomanip>
#include <numeric>
#include <chrono>


int main(int argc, char** args) { 
    auto argument = ProgramArgument::getInstance("mincrossing");
    argument->parseArguments(argc, args);
    Parser parser;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    Problem* problem = parser.parseProblem(argument->getFile());
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::milliseconds ellapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    size_t seed = argument->getSeed();
    if (seed != -1) {
        Random::setSeed(seed);
    }
    seed = Random::getSeed();
    std::cout << "Current seed: " << seed << "\n";
    std::cout << "Reading time: " << ellapsed.count() << "ms\n";
    if (argument->getLowerBound()) {
        BipartiteGraph& graph = problem->getGraph();
        std::cout << "Lower bound: " << graph.calculateMinimumCrossingLowerBound() << std::endl;
    } 
    else {
        StoppingCondition* stoppingCondition = argument->getStoppingCondition();
        Algorithm *algorithm = argument->getAlgorithm();
        std::vector<int> record;
        long long min=-1, max=-1;
        double sum = 0;
        for (int repetition = argument->getRepetition(); repetition > 0; repetition--) {
            if (problem != nullptr && algorithm != nullptr) {
                std::cout << "Repetition: " << record.size();
                start = std::chrono::steady_clock::now();
                Solution solution = problem->findSolution(algorithm, stoppingCondition);
                end = std::chrono::steady_clock::now();
                ellapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                std::cout << "(" << ellapsed.count() << "ms)\n";
                sum += solution.minCrossing;
                if (min == -1 || solution.minCrossing < min) min = solution.minCrossing;
                if (max == -1 || solution.minCrossing > max) max = solution.minCrossing;
                record.push_back(solution.minCrossing);
            }
        }

        std::string delimiter = ",";
        std::string result;

        for (size_t i = 0; i < record.size(); ++i) {
            result += std::to_string(record[i]);

            if (i < record.size() - 1) {
                result += delimiter;
            }
        }
        std::cout << result << std::endl;
        std::cout << "Max: " << max << std::endl;
        std::cout << "Average: " << std::fixed << std::setprecision(2) << sum / record.size() << std::endl;
        std::cout << "Min: " << min << std::endl;
        delete algorithm;
    }
    delete problem;
    return 1;
} 