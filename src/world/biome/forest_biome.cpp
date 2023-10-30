#include "world/biome/forest_biome.h"
#include "treebuilder.h"
#include "game.h"
#include "randomgenerator.h"

void ForestBiome::makeTree(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const {
    Game& game = Game::getInstance();
    World& world = game.getWorld();
    int treeFrequency = 16;
    RandomGenerator& random = RandomGenerator::getInstance();
    if (random.randInt(0, treeFrequency) == 0) {
        if (random.randInt(0, 20) == 0) {
            chunk->addBlock(x, y + 1, z, Material::GRASS_ITEM.getID());
        } else {
            int trunkHeight = 3 + random.randInt(0, 2);
            buildTree(chunk, x, z, trunkHeight, y);
        }
    }
}

void ForestBiome::makeFlower(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const {

}

Material ForestBiome::getTopMaterial() const {
    return Material::GRASS;
}

Material ForestBiome::getUndergroundMaterial() const {
    return Material::DIRT;
}

Material ForestBiome::getUnderWaterMaterial() const {
    return Material::DIRT;
}

BiomeType ForestBiome::getBiomeType() const {
    return BiomeType::FOREST;
}

NoiseSettings ForestBiome::getNoiseSettings() const {
    NoiseSettings noiseSettings;
    noiseSettings.octaves = 7;
    noiseSettings.amplitude = 10.0f;
    noiseSettings.smoothness = 500.0f;
    noiseSettings.offset = 5.0f;
    noiseSettings.roughness = 0.5f;
    return noiseSettings;
}