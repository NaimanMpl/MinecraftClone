#include "world/biome/plains_biome.h"
#include "treebuilder.h"
#include "randomgenerator.h"

void PlainsBiome::makeTree(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const {
    
}

void PlainsBiome::makeFlower(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const {
    int flowerFrequency = 8;
    RandomGenerator& random = RandomGenerator::getInstance();
    int randomNumber = random.randInt(0, flowerFrequency);
    if (randomNumber == 0) {
        chunk->addBlock(x, y, z, Material::GRASS_ITEM.getID());
    } else if (randomNumber == 4) {
        chunk->addBlock(x, y, z, random.randInt(0, 1) == 0 ? Material::RED_FLOWER.getID() : Material::YELLOW_FLOWER.getID());
    }
}


Material PlainsBiome::getTopMaterial() const {
    return Material::GRASS;
}

Material PlainsBiome::getUndergroundMaterial() const {
    return Material::DIRT;
}

Material PlainsBiome::getUnderWaterMaterial() const {
    return Material::DIRT;
}

BiomeType PlainsBiome::getBiomeType() const {
    return BiomeType::PLAINS;
}

NoiseSettings PlainsBiome::getNoiseSettings() const {
    NoiseSettings noiseSettings;
    noiseSettings.octaves = 7;
    noiseSettings.amplitude = 30.0f;
    noiseSettings.smoothness = 800.0f;
    noiseSettings.offset = 25.0f;
    noiseSettings.roughness = 0.7f;
    return noiseSettings;
}