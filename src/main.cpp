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
#include <utils/simple_timer.h>


int main(int argc, char** args) { 
    auto argument = ProgramArgument::getInstance("mincrossing");
    argument->parseArguments(argc, args);
    Parser parser;
    Problem* problem = parser.parseProblem(argument->getFile());
    size_t seed = argument->getSeed();
    if (seed != -1) {
        Random::setSeed(seed);
    }
    seed = Random::getSeed();
    std::cout << "Current seed: " << seed << "\n";
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
                SimpleTimer timer;
                Solution solution = problem->findSolution(algorithm, stoppingCondition);
                std::cout << "(" << timer.count() << "ms)\n";
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