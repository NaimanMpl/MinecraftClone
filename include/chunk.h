#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include "game_configuration.h"
#include "block.h"
#include <glm/gtc/noise.hpp>

class Chunk {
    private:
        std::vector<Block> blocks;
        glm::ivec3 position;
        void initBlocks();
    public:
        Chunk();
        Chunk(int x, int y, int z);

        std::vector<Block>& getBlocks();
        glm::ivec3& getPosition();

        void addBlock(Block block);
};

#endif