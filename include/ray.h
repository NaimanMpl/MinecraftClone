#ifndef RAY_CLASS_H
#define RAY_CLASS_H

#include "world/chunk.h"

class Ray {
    private:
        int8_t block;
        Chunk* chunk;
    public:
        int blockX, blockY, blockZ;
        Ray();
        int8_t getBlock();
        int getBlockX();
        int getBlockY();
        int getBlockZ();
        Chunk* getChunk();

        void update();
};

#endif