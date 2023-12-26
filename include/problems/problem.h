#ifndef PROBLEM_H
#define PROBLEM_H

#include <algorithms/algorithm.h>

class Problem {
public:
    static Problem* parseProblem(const char ** string);
};

#endif