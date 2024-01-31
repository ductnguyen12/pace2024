#include <iostream>
#include <fstream>
#include <string>
#include <utils/random.h>
#include <unordered_set>
#include <utility>

#define MAX_N1 1000000

int main(int argc, char** args) {
    std::ofstream file(args[1]);
    if (!file.is_open()) {
        return -1;
    }
    Random& random = Random::getInstance();
    int n0 = std::stoi(args[2]);
    int n1 = std::stoi(args[3]);
    int m = std::stoi(args[4]);
    struct hashFunction
    {
        size_t operator()(const std::pair<int ,
                int> &x) const
        {
            return x.first * MAX_N1 + x.second;
        }
    };
    std::unordered_set<std::pair<int, int>, hashFunction> edges;
    while (m > 0) {
        int v0 = random.getInt(n0);
        int v1 = random.getInt(n1);
        edges.insert(std::make_pair(v0, v1));
        m--;
    }
    file << "p ocr " << n0 << " " << n1 << " " << edges.size() << std::endl;
    for (auto &edge : edges) {
        file << edge.first + 1 << " " << n0 + edge.second + 1 << std::endl;
    }
}
