#ifndef UTILITY_H
#define UTILITY_H

/**
 * @brief Function for swapping the values of the two integeres
*/
void swap(int &a, int &b);

template <class Iterator>
void flip(Iterator first, Iterator last);

int min(int a, int b);
int max(int a, int b);

#endif