#ifndef DEFAULT_WORLD_GENERATOR_CLASS_H
#define DEFAULT_WORLD_GENERATOR_CLASS_H

#include "terrain_generator.h"
#include <unordered_map>

class DefaultWorldGenerator: public TerrainGenerator {
    public:
        DefaultWorldGenerator();

        int calculateHeight(int x, int z) const override;
        void generateTerrain(Chunk* chunk) override;
};

#endif