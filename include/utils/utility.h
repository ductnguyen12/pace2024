#ifndef UTILITY_H
#define UTILITY_H

#include <utility>
#include <list>
#include <vector>
#include "graph/bipartite_graph.h"

/**
 * @brief Function for swapping the values of the two integeres
*/
void swap(int &a, int &b);

template <class Iterator>
void flip(Iterator first, Iterator last);

template <class Container>
Container extract(Container const& container, std::pair<int, int> const& locations);

std::list<int> generateList(int size);
std::vector<int> generateVector(int size);

int min(int a, int b);
int max(int a, int b);
int constraint(int value, int left, int right);

template <typename Container>
int countDelta(BipartiteGraph& graph, std::pair<int, int>& range, Container oldOrder, Container newOrder);

unsigned long long shiftPartialOrder(BipartiteGraph& graph, std::vector<int>::iterator begin, std::vector<int>::iterator end, bool right);

std::vector<int> applyMedianHeuristic(BipartiteGraph *graph);
std::vector<int> applyBarycentricHeuristic(BipartiteGraph *graph);
std::vector<int> getRandomOrder(BipartiteGraph *graph);

#endif