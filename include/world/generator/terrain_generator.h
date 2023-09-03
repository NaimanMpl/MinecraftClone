#ifndef TERRAIN_GENERATOR_CLASS_H
#define TERRAIN_GENERATOR_CLASS_H

class Chunk;

class TerrainGenerator {
    public:
        virtual void generateTerrain(Chunk* chunk) = 0;
        virtual int calculateHeight(int x, int z) const = 0;
};

#endif