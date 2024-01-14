#ifndef UTILITY_H
#define UTILITY_H

#include <utility>
#include <list>

/**
 * @brief Function for swapping the values of the two integeres
*/
void swap(int &a, int &b);

template <class Iterator>
void flip(Iterator first, Iterator last);

template <class Container>
Container extract(Container const& container, std::pair<int, int> const& locations);

std::list<int> generateList(int size);

int min(int a, int b);
int max(int a, int b);
int constraint(int value, int left, int right);

#endif