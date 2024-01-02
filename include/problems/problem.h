#ifndef PROBLEM_H
#define PROBLEM_H

#include <algorithms/algorithm.h>
#include <algorithms/solution.h>

class Problem {
public:
    Solution findSolution(Algorithm& algorithm) = 0;

    static Problem* parseProblem(const char ** string);
};

#endif