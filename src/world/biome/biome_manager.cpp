#include "world/biome/biome_manager.h"
#include "world/generator/noise_generator.h"

Biome* BiomeManager::FOREST_BIOME = new ForestBiome();
Biome* BiomeManager::DESERT_BIOME = new DesertBiome();
Biome* BiomeManager::PLAINS_BIOME = new PlainsBiome();

Biome* BiomeManager::determineBiome(float x, float z) {
    float biomeValue = NoiseGenerator::getHeight(x, z, NoiseGenerator::BIOME_NOISE_SETTINGS);
    if (biomeValue < 950) {
        return DESERT_BIOME;
    } else if (biomeValue < 1050) {
        return PLAINS_BIOME;
    } else if (biomeValue < 1450) {
        return FOREST_BIOME;
    } else {
        return PLAINS_BIOME;
    }
}