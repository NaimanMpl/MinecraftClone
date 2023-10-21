#ifndef RAY_CLASS_H
#define RAY_CLASS_H

#include "world/chunk.h"

class Ray {
    private:
        int8_t block;
        Chunk* chunk;
        glm::vec3 normal;
    public:
        int blockX, blockY, blockZ;
        Ray();
        int8_t getBlock();
        int getBlockX();
        int getBlockY();
        int getBlockZ();
        Chunk* getChunk();
        glm::vec3 getNormal();

        void update();
};

#endif