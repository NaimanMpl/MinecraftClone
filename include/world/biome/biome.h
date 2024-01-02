#ifndef BIOME_CLASS_H
#define BIOME_CLASS_H

#include <string>
#include "world/material.h"
#include "world/world.h"
#include "world/generator/noise_generator.h"

enum BiomeType {
    PLAINS,
    FOREST,
    MOUNTAINS,
    DESERT,
    OCEANS
};

class Biome {
    protected:
        BiomeType type;
    private:

    public:
        Biome() = default;
        
        virtual void makeTree(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const = 0;
        virtual void makeFlower(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const = 0;
        
        virtual Material getTopMaterial() const = 0;
        virtual Material getUndergroundMaterial() const = 0;
        virtual Material getUnderWaterMaterial() const = 0;
        virtual BiomeType getBiomeType() const = 0;
        virtual NoiseSettings getNoiseSettings() const = 0;

        float getHeight(int x, int z);
};

#endif
