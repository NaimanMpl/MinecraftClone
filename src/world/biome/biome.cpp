#include "world/biome/biome.h"

float Biome::getHeight(int x, int z) {
    return static_cast<float>(NoiseGenerator::getHeight(x, z, this->getNoiseSettings()));
}