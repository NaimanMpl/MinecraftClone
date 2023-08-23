#ifndef RAY_CLASS_H
#define RAY_CLASS_H

#include "world/chunk.h"

class Ray {
    private:
        Block* block;
        Chunk* chunk;
    public:
        Ray();
        Block* getBlock();
        Chunk* getChunk();

        void update();
};

#endif