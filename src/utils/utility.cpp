#include <utils/utility.h>
#include <vector>
#include <list>

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

template <class Iterator>
void flip(Iterator first, Iterator last){
    if (first == last) return;
    last--;
    while (first != last) {
        swap(*first, *last);
        if (++first == last--) break;
    }
    return;
}

template void flip<std::vector<int>::iterator>(std::vector<int>::iterator first, std::vector<int>::iterator second);
template void flip<std::list<int>::iterator>(std::list<int>::iterator first, std::list<int>::iterator second);

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}