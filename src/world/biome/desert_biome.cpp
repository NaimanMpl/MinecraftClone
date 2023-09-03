#include "world/biome/desert_biome.h"
#include "treebuilder.h"

void DesertBiome::makeTree(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const {
    if (rand() % 30 == 0) {
        int cactusHeight = 4;
        if (cactusHeight + y < CHUNK_SIZE && x + 4 < CHUNK_SIZE && z + 4 < CHUNK_SIZE) {
            buildCactus(chunk, x, z, cactusHeight, y);
        }
    }
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