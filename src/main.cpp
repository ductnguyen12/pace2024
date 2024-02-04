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
#include <numeric>

int main(int argc, char** args) {
    auto argument = ProgramArgument::getInstance("mincrossing");
    argument->parseArguments(argc, args);
    Parser parser;
    Problem* problem = parser.parseProblem(argument->getFile());
    StoppingCondition* stoppingCondition = argument->getStoppingCondition();
    Algorithm *algorithm = argument->getAlgorithm();
    std::vector<int> record;
    int sum=0, min=-1, max=-1;
    for (int repetition = argument->getRepetition(); repetition > 0; repetition--) {
        if (problem != nullptr && algorithm != nullptr) {
            Solution solution = problem->findSolution(algorithm, stoppingCondition);
            sum += solution.minCrossing;
            if (min == -1 || solution.minCrossing < min) min = solution.minCrossing;
            if (max == -1 || solution.minCrossing > max) max = solution.minCrossing;
            record.push_back(solution.minCrossing);
            std::cout << "Repetition: " << record.size() << std::endl;
        }
    }
    // Using a loop to concatenate strings with a delimiter
    std::string delimiter = ",";
    std::string result;

    for (size_t i = 0; i < record.size(); ++i) {
        result += std::to_string(record[i]);

        // Add the delimiter except for the last element
        if (i < record.size() - 1) {
            result += delimiter;
        }
    }
    std::cout << result << std::endl;
    std::cout << "Max: " << max << std::endl;
    std::cout << "Average: " << (double) sum / record.size() << std::endl;
    std::cout << "Min: " << min << std::endl;
    const BipartiteGraph& graph = problem->getGraph();
    std::cout << "Lower bound: " << graph.calculateMinimumCrossingLowerBound() << std::endl;
    delete problem;
    delete algorithm;
    return 1;
}