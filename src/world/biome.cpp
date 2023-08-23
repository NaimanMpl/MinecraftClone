#include "world/biome.h"

const Biome Biome::FOREST = Biome(BiomeType::FOREST, 0.02);
const Biome Biome::PLAINS = Biome(BiomeType::PLAINS, 0.02);
const Biome Biome::DESERT = Biome(BiomeType::DESERT, 0.02);
const Biome Biome::MOUNTAINS = Biome(BiomeType::MOUNTAINS, 0.02);

Biome::Biome(BiomeType type, double frequency) {
    this->type = type;
    this->frequency = frequency;
}

double Biome::getFrenquency() {
    return this->frequency;
}

BiomeType Biome::getType() {
    return this->type;
}