#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include "../game_configuration.h"
#include "block.h"
#include <glm/gtc/noise.hpp>

const int CHUNK_SIZE = 16;
const int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
const int CHUNK_VOL = CHUNK_AREA * CHUNK_SIZE;
const int CHUNK_SPHERE_RADIUS = CHUNK_SIZE * sqrt(3) / 2;

class Chunk {
    private:
        Block* blocks[CHUNK_VOL] = {nullptr};
        glm::ivec3 position;
        void initBlocks();
    public:
        Chunk();
        Chunk(int x, int y, int z);

        glm::ivec3& getPosition();
        Block* getBlock(int x, int y, int z);
        Block** getBlocks();
        int getX();
        int getY();
        int getZ();

        void addBlock(Block* block);
        void setBlock(int x, int y, int z, Block* block);
        float noise2D(int8_t x, int8_t z, float size, float height, float shift);
};

#endif