#include <utils/utility.h>
#include <vector>
#include <list>
#include <iostream>
#include <utils/random.h>
#include <map>

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

template <class Container>
Container extract(Container const& container, std::pair<int, int> const& locations) {
    int left = locations.first;
    int right = locations.second;
    if (left > right) swap(left, right);
    left = constraint(left, 0, container.size());
    right = constraint(right + 1, 0, container.size());
    auto leftIter = std::next(container.begin(), left);
    auto rightIter = std::next(container.begin(), right);
    return Container(leftIter, rightIter);
}
template std::list<int> extract(std::list<int> const& container, std::pair<int, int> const& locations);
template std::vector<int> extract(std::vector<int> const& container, std::pair<int, int> const& locations);

std::list<int> generateList(int size) {
    std::list<int> result;
    for (int i = 0; i < size; i++) result.push_back(i);
    return result;
}

std::vector<int> generateVector(int size) {
    std::vector<int> result;
    for (int i = 0; i < size; i++) result.push_back(i);
    return result;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int constraint(int value, int left, int right) {
    if (right < left) swap(left, right);
    return min(max(value, left), right);
}

std::vector<int> applyMediumHeuristic(BipartiteGraph *graph){
    std::vector<int>order;
    if(graph!=NULL){
        int n1 = graph ->getN1();
        std::vector<std::vector<int>> adj = graph -> getVs1();
        std::map<int,std::vector<int>> m;

        for(int i=0;i<n1;++i){
            int md = adj[i].size()/2;
            m[i].push_back(md);
        }
        for(auto u:m){
            for(auto v:u.second){
                order.push_back(v);
            }
        }
    }
    return order;
}

std::vector<int> applyBarycentricHeuristic(BipartiteGraph *graph){
    std::vector<int>order;
    if(graph!=NULL){
        int n1 = graph ->getN1();
        std::vector<std::vector<int>> adj = graph -> getVs1();
        std::map<int,std::vector<int>> m;

        for(int i=0;i<n1;++i){
            int sum = 0;
            for(auto u:adj[i]){
                sum+=u;
            }
            int barycenter = sum / adj[i].size();
            m[i].push_back(barycenter);
        }
        for(auto u:m){
            for(auto v:u.second){
                order.push_back(v);
            }
        }
    }
    return order;
}
