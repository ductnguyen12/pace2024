#include <utils/random.h>
#include <chrono>
#include <list>
#include <vector>

size_t* Random::seed = nullptr;
Random* Random::instance = nullptr;

Random::Random() {
    std::random_device rd;
    if (seed == nullptr) {
        seed = new size_t(std::chrono::system_clock::now().time_since_epoch().count());
    }
    generator = std::mt19937(*seed);
}

Random& Random::getInstance() {
    static Random instance;
    return instance;
}

bool Random::setSeed(size_t seed) {
    if (Random::seed == nullptr) {
        Random::seed = new size_t(seed);
        getInstance();
        return true;
    }
    return false;
}

size_t Random::getSeed() {
    if (seed == nullptr) {
        seed = new size_t(std::chrono::system_clock::now().time_since_epoch().count());
    }
    return *seed;
}

int Random::getInt(int min, int max) {
    std::uniform_int_distribution<int> distribution(min, max - 1);
    return distribution(generator);
}

int Random::getInt(int max) {
    return getInt(0, max);
}

template <class Container>
void Random::shuffle(Container& container) {
    if constexpr (std::is_same_v<Container, std::vector<int>>) {
        std::shuffle(container.begin(), container.end(), generator);
    }
    else {
        std::vector<int> vector(container.begin(), container.end());
        shuffle(vector);
        container.clear();
        std::move(vector.begin(), vector.end(), std::back_inserter(container));
    }
}
template void Random::shuffle(std::vector<int>& container);
template void Random::shuffle(std::list<int>& container);

bool Random::randOutcome(float prob) {
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return prob > distribution(generator);
}