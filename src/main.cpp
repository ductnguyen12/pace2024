#include <iostream>
#include <graph/bipartite_graph.h>
#include <algorithms/brute_force.h>
#include <utils/argument.h>
#include <problems/problem.h>

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
    DummyStoppingCondition stoppingCondition;
    BruteForceAlgorithm alg(stoppingCondition);
    Solution solution = alg.findSolution(&graph);

    std::cout << "Min crossing: " << solution.minCrossing << "\nOrder: ";
    if (solution.order != nullptr) for (int i : *(solution.order)) std::cout << n0 + i + 1 << " ";
    std::cout << std::endl;
#ifdef DEBUG_MODE
    Parser parser;
    Problem* problem = parser.parseProblem("examples/OCR/cycle_8_shuffled.gr");
    if (problem != nullptr) {
        Solution solution = problem->findSolution(alg);
        std::cout << "Min crossing: " << solution.minCrossing << "\nOrder: ";
        if (solution.order != nullptr) for (int i : *(solution.order)) std::cout << n0 + i + 1 << " ";
        std::cout << std::endl;
    }

#endif
    return 1;
}