#include "world/biome/biome_manager.h"
#include "world/generator/noise_generator.h"

BiomeManager::BiomeManager() {
    forestBiome = new ForestBiome();
    desertBiome = new DesertBiome();
    plainsBiome = new PlainsBiome();
}

Biome* BiomeManager::determineBiome(float x, float z, float altitude) {
    float biomeValue = NoiseGenerator::getHeight(x, z, NoiseGenerator::BIOME_NOISE_SETTINGS);
    if (biomeValue < 950) {
        return desertBiome;
    } else if (biomeValue < 1150) {
        return plainsBiome;
    } else if (biomeValue < 1250) {
        return forestBiome;
    } else {
        return plainsBiome;
    }
}