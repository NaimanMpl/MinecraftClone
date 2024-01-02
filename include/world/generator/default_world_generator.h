#ifndef DEFAULT_WORLD_GENERATOR_CLASS_H
#define DEFAULT_WORLD_GENERATOR_CLASS_H

#include <unordered_map>
#include "terrain_generator.h"
#include <cstddef>

struct HeightKey {
    int x;
    int z;

    bool operator==(const HeightKey& other) const {
        return x == other.x && z == other.z;
    }
};

struct HeightKeyHash {
    size_t operator()(const HeightKey& coordinates) const {
        size_t xHash = std::hash<int>{}(coordinates.x);
        size_t zHash = std::hash<int>{}(coordinates.z);

        return xHash ^ (zHash << 1);
    }
};

class DefaultWorldGenerator: public TerrainGenerator {
    private:
        Chunk* chunk;
        float** heightMap;
    public:
        DefaultWorldGenerator();

        int calculateHeight(int x, int z) const override;
        void generateTerrain(Chunk* chunk) override;
};

#endif