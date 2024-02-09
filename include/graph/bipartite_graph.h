#ifndef BIPARTITE_GRAPH_H
#define BIPARTITE_GRAPH_H

#include <vector>
#include <list>
#include <iterator>

class BipartiteGraph {
private:
    // Total number of vertices of the first layer and second layer
    int n0, n1;

    // Lists of connected vertices of the layers
    std::vector<std::vector<int>> vs0, vs1;

    /**
     * @brief Count the number of crossing edges between the first layer and 
     * two list of vertices @v1 and @v2 where @v1 comes first
     * @param v1: the sorted list of connected vertice of the first vertex
     * @param v2: the sorted list of connected vertice of the second vertex
     * @note @v1 and @v2 must be sorted
     * @return the number of crossing edges
    */
    static int __count(std::vector<int> const& v1, std::vector<int> const& v2);
    std::vector<std::vector<int>> cache;
public:
    BipartiteGraph(int n0, int n1, const std::vector<std::vector<int>>& vs1);
    ~BipartiteGraph();

    int getN0() const;
    int getN1() const;
    const std::vector<std::vector<int>>& getVs0() const;
    const std::vector<std::vector<int>>& getVs1() const;

    /**
     * @brief Count the number of crossing edges between the first layer and
     * a second layer provided by the order of the type @Container
     * @param order: the ordered list of vertices of the second layer
     * @note `order` must has the .begin() and .end() as iterators
     * @return the number of crossing edges
    */
    template <class Container>
    int count(Container const& order);
    int count(int i1, int i2);
    [[nodiscard]] const std::vector<std::vector<int>>& computeCrossingMatrix();
    long long calculateMinimumCrossingLowerBound();
};

#endif