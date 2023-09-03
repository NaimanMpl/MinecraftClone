#include "world/biome/plains_biome.h"
#include "treebuilder.h"

void PlainsBiome::makeTree(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const {
    
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