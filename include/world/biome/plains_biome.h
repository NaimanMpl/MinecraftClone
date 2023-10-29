#ifndef PLAINS_BIOME_CLASS_H
#define PLAINS_BIOME_CLASS_H

#include "biome.h"

class PlainsBiome: public Biome {
    public:
        
        void makeTree(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const override;
        void makeFlower(Chunk* chunk, unsigned int x, unsigned int y, unsigned int z) const override;
        
        Material getTopMaterial() const override;
        Material getUndergroundMaterial() const override;
        Material getUnderWaterMaterial() const override;
        BiomeType getBiomeType() const override;
        NoiseSettings getNoiseSettings() const override;
};

#endif