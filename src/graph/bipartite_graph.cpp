#include <graph/bipartite_graph.h>
#include <algorithm>
#include <iostream>

BipartiteGraph::BipartiteGraph(int n0, int n1, const std::vector<std::vector<int>>& vs1) : n0(n0), n1(n1) {
    if (n1 > vs1.size()) {
        throw std::invalid_argument("There are fewer vertices from the edge list than given number of vertices (n1)");
    }
    for (int idx = 0; idx < n1; idx++) {
        BipartiteGraph::vs1.push_back(vs1.at(idx));
        std::sort(BipartiteGraph::vs1.at(idx).begin(), BipartiteGraph::vs1.at(idx).end());
    }
}
BipartiteGraph::~BipartiteGraph() { 
    
}

int BipartiteGraph::getN0() const { return n0; }
int BipartiteGraph::getN1() const { return n0; }
const std::vector<std::vector<int>>& BipartiteGraph::getVs1() const { return vs1; }


template <class Container>
int BipartiteGraph::count(Container const& order) const {
    int result = 0;
    for (auto left = order.begin(); left != order.end(); left++) {
        for (auto right = std::next(left); right != order.end(); right++) {
            result += count(vs1[*left], vs1[*right]);
        }
    }   
    
    return result;
}
template int BipartiteGraph::count(std::vector<int> const& order) const;
template int BipartiteGraph::count(std::list<int> const& order) const;


int BipartiteGraph::count(std::vector<int> const& v1, std::vector<int> const& v2) {
    if (v1.size() == 0 || v2.size()  == 0) {
        return 0;
    }
    int a = 0, b = v1.size() - 1, c = 0, d = v2.size() - 1, result = 0;
    while (a < b && v1.at(a) <= v2.at(0)) a++;
    while (d > c && v2.at(d) >= v1.at(v1.size() - 1)) d--;
    for (int i = a; i <= b; i++) {
        for (int j = c; j <= d; j++) {
            if (v2.at(j) < v1.at(i)) result += 1;
            else break;
        }
    }
    return result;
}