#include <graph/bipartite_graph.h>
#include <algorithm>
#include <iostream>

BipartiteGraph::BipartiteGraph(int n0, int n1, const std::vector<std::vector<int>>& vs1) : n0(n0), n1(n1) {
    if (n1 > vs1.size()) {
        throw std::invalid_argument("There are fewer vertices from the edge list than given number of vertices (n1)");
    }
    for (int idx = 0; idx < n0; idx++) {
        vs0.emplace_back();
    }
    for (int idx = 0; idx < n1; idx++) {
        this->vs1.push_back(vs1[idx]);
        std::sort(this->vs1[idx].begin(), this->vs1[idx].end());
        for (int v : this->vs1[idx]) {
            vs0[v].push_back(idx);
        }
    }
}
BipartiteGraph::~BipartiteGraph() { 
    
}

int BipartiteGraph::getN0() const { return n0; }
int BipartiteGraph::getN1() const { return n1; }
const std::vector<std::vector<int>>& BipartiteGraph::getVs0() const { return vs0; }
const std::vector<std::vector<int>>& BipartiteGraph::getVs1() const { return vs1; }


template <class Container>
int BipartiteGraph::count(Container const& order) const {
    int result = 0;
    for (auto left = order.begin(); left != order.end(); left++) {
        for (auto right = std::next(left); right != order.end(); right++) {
            result += __count(vs1[*left], vs1[*right]);
        }
    }   
    
    return result;
}
template int BipartiteGraph::count(std::vector<int> const& order) const;
template int BipartiteGraph::count(std::list<int> const& order) const;

int BipartiteGraph::__count(std::vector<int> const& v1, std::vector<int> const& v2) {
    if (v1.size() == 0 || v2.size()  == 0) {
        return 0;
    }
    int a = 0, b = v1.size() - 1, c = 0, d = v2.size() - 1, result = 0;
    while (a < b && v1[a] <= v2[0]) a++;
    while (d > c && v2[d] >= v1[v1.size() - 1]) d--;
    for (int i = a; i <= b; i++) {
        for (int j = c; j <= d; j++) {
            if (v2[j] < v1[i]) result += 1;
            else break;
        }
    }
    return result;
}

const std::vector<std::vector<int>> &BipartiteGraph::computeCrossingMatrix() const {
    auto* matrix = new std::vector<std::vector<int>>();
    for (int i = 0; i < n1; i++) {
        matrix->emplace_back();
        for (int j = 0; j < n1; j++) {
            if (i == j) {
                matrix->at(i).push_back(0);
                continue;
            }
            matrix->at(i).push_back(__count(vs1[i], vs1[j]));
        }
    }
    return *matrix;
}
