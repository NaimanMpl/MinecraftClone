#include "randomgenerator.h"

RandomGenerator::RandomGenerator() {
    rng.seed(this->seed);
}

int RandomGenerator::randInt(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

uint8_t RandomGenerator::getSeed() {
    return this->seed;
}