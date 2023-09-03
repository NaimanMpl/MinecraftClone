#ifndef BIOME_MANAGER_CLASS_H
#define BIOME_MANAGER_CLASS_H

#include "world/biome/desert_biome.h"
#include "world/biome/forest_biome.h"
#include "world/biome/plains_biome.h"

class BiomeManager {
    private:
        Biome* forestBiome;
        Biome* desertBiome;
        Biome* plainsBiome;
    public:
        BiomeManager();
        Biome* determineBiome(float x, float z, float altitude);
};

#endif