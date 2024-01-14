#ifndef RANDOM_H
#define RANDOM_H
#include <random>
#include <algorithm>


/**
 * @brief A singleton instance of the random number generator
*/
class Random {
private:
    Random();
    Random(const Random&) = delete;
    Random& operator=(const Random&) = delete;
    static uint* seed;
    static Random* instance;
    std::mt19937 generator;
public:
    /**
     * @brief Construct the random number generator instance with the given seed. 
     * If none is provided, the seed is initialized to the current time.
    */
    static Random& getInstance();
    static bool setSeed(uint seed);
    static uint getSeed();

    /**
     * @brief Get a random integer from the given range
     * @param min the inclusive minimum integer
     * @param max the exclusive maximum integer
     * @return a random integer between `min` and `max`-1
    */
    int getInt(int min, int max);

    /**
     * @brief Get a random integer up to a give integer
     * @param max the exclusive maximum integer
     * @return a random integer between 0 and `max`-1
    */
    int getInt(int max);

    /**
     * @brief Shuffle a container
     * @param container the containter to shuffle, supposed to be a vector or a list
    */
    template <class Container>
    void shuffle(Container& container);

    bool randOutcome(float prob);    
};
#endif