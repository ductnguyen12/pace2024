#include <iostream>
#include <graph/bipartite_graph.h>
#include <algorithms/brute_force.h>
#include <utils/argument.h>
#include <problems/problem.h>
#include <stopping_conditions/time_stopping_condition.h>
#include <algorithms/random_search.h>
#include <algorithms/simulated_annealing.h>

int main(int argc, char** args) {
    auto argument = ProgramArgument::getInstance("mincrossing");
    argument->parseArguments(argc, args);

    /**
     * An example:
     * 4 5 8
     * 1 7
     * 2 5
     * 2 6
     * 2 8
     * 2 9
     * 3 6
     * 4 7
     * 4 8
     * **/
    std::vector<std::vector<int>> vs = {
        {1}, {1, 2}, {0, 3}, {1, 3}, {1}
    };
    int n0 = 4;
    int n1 = 5;
    int m = 8;
    BipartiteGraph graph(n0, n1, vs);
    TimeStoppingCondition stoppingCondition(0.01*1000000);
    SimulatedAnnealing alg(stoppingCondition);
    Solution solution = alg.findSolution(&graph);

    std::cout << "Min crossing: " << solution.minCrossing << "\nOrder: ";
    if (solution.order != nullptr) for (int i : *(solution.order)) std::cout << n0 + i + 1 << " ";
    std::cout << std::endl;
#ifdef DEBUG_MODE
    Parser parser;
    Problem* problem = parser.parseProblem("C:\\Users\\LENOVO\\Desktop\\Graph lab\\pace2024\\examples\\OCR\\tree_6_10.gr");
    if (problem != nullptr) {
        Solution solution = problem->findSolution(alg);
        std::cout << "Min crossing: " << solution.minCrossing << "\nOrder: ";
        if (solution.order != nullptr) for (int i : *(solution.order)) std::cout << n0 + i + 1 << " ";
        std::cout << std::endl;
    }

#endif
    return 1;
}