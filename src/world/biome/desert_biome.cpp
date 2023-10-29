#include "world/biome/desert_biome.h"
#include "treebuilder.h"
#include "randomgenerator.h"

void DesertBiome::makeTree(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const {
    int cactusFrequency = 8;
    RandomGenerator& random = RandomGenerator::getInstance();
    if (random.randInt(0, cactusFrequency) == 0) {
        int cactusHeight = 4;
        if (cactusHeight + y < CHUNK_SIZE && x + 4 < CHUNK_SIZE && z + 4 < CHUNK_SIZE) {
            buildCactus(chunk, x, z, cactusHeight, y);
        }
    }
    chunk->setTreeBuilt(true);
}

void DesertBiome::makeFlower(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const {
    
}

Material DesertBiome::getTopMaterial() const {
    return Material::SAND;
}

Material DesertBiome::getUndergroundMaterial() const {
    return Material::SAND;
}

Material DesertBiome::getUnderWaterMaterial() const {
    return Material::SAND;
}

BiomeType DesertBiome::getBiomeType() const {
    return BiomeType::DESERT;
}

NoiseSettings DesertBiome::getNoiseSettings() const {
    NoiseSettings noiseSettings;
    noiseSettings.octaves = 7;
    noiseSettings.amplitude = 10.0f;
    noiseSettings.smoothness = 300.0f;
    noiseSettings.offset = 57.0f;
    noiseSettings.roughness = 0.7f;
    return noiseSettings;
}