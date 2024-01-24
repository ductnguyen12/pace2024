#include <iostream>
#include <graph/bipartite_graph.h>
#include <algorithms/brute_force.h>
#include <utils/argument.h>
#include <problems/problem.h>
#include <utils/utility.h>
#include <utils/random.h>
#include <stopping_conditions/time_stopping_condition.h>
#include <algorithms/genetic_algorithm.h>

int main(int argc, char** args) {
    auto argument = ProgramArgument::getInstance("mincrossing");
    argument->parseArguments(argc, args);
    Parser parser;
    Problem* problem = parser.parseProblem(argument->getFile());
    StoppingCondition* stoppingCondition = argument->getStoppingCondition();
    Algorithm *algorithm = argument->getAlgorithm(*stoppingCondition);
    if (problem != nullptr && algorithm != nullptr) {
        Solution solution = problem->findSolution(*algorithm);
        int n0 = problem->getGraph().getN0();
        std::cout << "Min crossing: " << solution.minCrossing << "\nOrder: ";
        if (solution.order != nullptr) for (int i : *(solution.order)) std::cout << i + 1 + n0 << " ";
        std::cout << std::endl;
    }
    delete problem;
    delete algorithm;
    return 1;
}