#include "world/biome/forest_biome.h"
#include "treebuilder.h"
#include "game.h"
#include "randomgenerator.h"

void ForestBiome::makeTree(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const {
    Game& game = Game::getInstance();
    World& world = game.getWorld();
    int treeFrequency = 4;
    RandomGenerator& random = RandomGenerator::getInstance();
    if (random.randInt(0, treeFrequency) == 0) {
        int trunkHeight = 3 + random.randInt(0, 2);
        buildTree(chunk, x, z, trunkHeight, y);
    }
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