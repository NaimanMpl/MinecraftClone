#include "world/biome/forest_biome.h"
#include "treebuilder.h"

void ForestBiome::makeTree(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const {
    if (rand() % 10 == 0) {
        int trunkHeight = 3 + rand() % 3;
        if (trunkHeight + y < CHUNK_SIZE && x + 4 < CHUNK_SIZE && z + 4 < CHUNK_SIZE) {
            buildTree(chunk, x, z, trunkHeight, y);
        }
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