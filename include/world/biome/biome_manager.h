#ifndef BIOME_MANAGER_CLASS_H
#define BIOME_MANAGER_CLASS_H

#include "world/biome/desert_biome.h"
#include "world/biome/forest_biome.h"
#include "world/biome/plains_biome.h"

class BiomeManager {
    public:
        static Biome* FOREST_BIOME;
        static Biome* DESERT_BIOME;
        static Biome* PLAINS_BIOME;
        static Biome* determineBiome(float x, float z);
};

#endif