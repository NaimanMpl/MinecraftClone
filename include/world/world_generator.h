#ifndef WORLD_GENERATOR_H
#define WORLD_GENERATOR_H

#include <cstdint>
#include "biome.h"

class WorldGenerator {
    public:

        static Biome determineBiome(float biomeNoiseValue);
        static float getBiomeNoise(float x, float z);
        static float getTerrainNoise(float x, float z);
};

#endif