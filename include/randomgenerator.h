#ifndef RANDOM_GENERATOR_CLASS_H
#define RANDOM_GENERATOR_CLASS_H

#include <random>

class RandomGenerator {
    private:
        std::mt19937 rng;
        uint8_t seed = 200;

        RandomGenerator();
    public:

        static RandomGenerator& getInstance() {
            static RandomGenerator instance;
            return instance;
        }

        RandomGenerator(const RandomGenerator&) = delete;
        void operator=(const RandomGenerator&) = delete;

        int randInt(int min, int max);
        uint8_t getSeed();
};

#endif