#ifndef BIPARTITE_GRAPH_H
#define BIPARTITE_GRAPH_H

#include <vector>
#include <list>
#include <iterator>

class BipartiteGraph {
private:
    // Total number of vertices of the first layer and second layer
    int n0, n1;

    // Lists of connected vertices of the second layer
    std::vector<std::vector<int>> vs1;

public:
    BipartiteGraph(int n0, int n1, const std::vector<std::vector<int>>& vs1);
    ~BipartiteGraph();

    int getN0() const;
    int getN1() const;
    const std::vector<std::vector<int>>& getVs1() const;

    // Count the number of crossing edges between the first layer 
    // and the second layer by the given order
    template <class Container>
    int count(Container const& order) const;

    static int count(std::vector<int> const& v1, std::vector<int> const& v2);
};

#endif