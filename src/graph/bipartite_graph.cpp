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
unsigned long long BipartiteGraph::count(Container const& order) {
    unsigned long long result = 0;
    for (auto left = order.begin(); left != order.end(); left++) {
        for (auto right = std::next(left); right != order.end(); right++) {
            result += count(*left, *right);
        }
    }   
    
    return result;
}
template unsigned long long BipartiteGraph::count(std::vector<int> const& order); 
template unsigned long long BipartiteGraph::count(std::list<int> const& order);

unsigned long long BipartiteGraph::__count(std::vector<int> const& v1, std::vector<int> const& v2) {
    if (v1.size() == 0 || v2.size()  == 0) {
        return 0;
    }
    int a = 0, b = v1.size() - 1, c = 0, d = v2.size() - 1;
    while (a < b && v1[a] <= v2[0]) a++;
    while (d > c && v2[d] >= v1[v1.size() - 1]) d--;
    unsigned long long result = 0, gap = 1;
    for (int i = a, j = c; i <= b; i++) {
        while (v2[j] < v1[i] && j <= d) {
            j++;
            gap++;
        }
        result += gap;
    }
    return result;
}

unsigned long long BipartiteGraph::count(int i1, int i2) {
    unsigned long long hashed = (unsigned long long) n1 * i1 + i2;
    if (!cache.count(hashed)) cache[hashed] = __count(vs1[i1], vs1[i2]);
    return cache[hashed];
}

std::vector<std::vector<unsigned long long>> BipartiteGraph::computeCrossingMatrix() {
    std::vector<std::vector<unsigned long long>> matrix;
    matrix.resize(n1);
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n1; j++) {
            matrix[i].push_back(i == j ? 0 : count(i, j));
        }
    }
    return matrix;
}

unsigned long long BipartiteGraph::calculateMinimumCrossingLowerBound() {
    unsigned long long sum = 0;
    for (int i = 0, n1 = n0; i < n1; i++) {
        for (int j = i + 1; j < n1; j++) {
            sum += std::min(count(i, j), count(j, i));
        }
    }
    return sum;
}

void BipartiteGraph::clearCache() {
    cache.clear();
}