#ifndef SOLUTION_H
#define SOLUTION_H

#include <vector>

/**
 * @brief A solution struct containing a minimum number of crossing edges
 * and its corresponding ordered list of vertices.
*/
struct Solution {
    long long minCrossing;
    std::vector<int>* order;
    ~Solution() {
        delete order;
    }
};

#endif