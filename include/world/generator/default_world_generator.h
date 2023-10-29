#ifndef DEFAULT_WORLD_GENERATOR_CLASS_H
#define DEFAULT_WORLD_GENERATOR_CLASS_H

#include <unordered_map>
#include "terrain_generator.h"

class DefaultWorldGenerator: public TerrainGenerator {
    public:
        DefaultWorldGenerator();

        int calculateHeight(int x, int z) const override;
        void generateTerrain(Chunk* chunk) override;
};

#endif