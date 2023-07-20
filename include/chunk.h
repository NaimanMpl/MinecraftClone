#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include "game_configuration.h"
#include "block.h"

class Chunk {
    private:
        std::vector<Block> blocks;
        glm::vec3 origin;
    public:
        Chunk();
        Chunk(std::vector<Block> blocks, glm::vec3 origin);

        std::vector<Block>& getBlocks();
        glm::vec3& getOrigin();

        void addBlock(Block block);
};

#endif