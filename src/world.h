#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include "block.h"
#include <vector>

enum WorldType { DEFAULT, FLAT };
static const int WORLD_WIDTH = 10;
static const int WORLD_HEIGHT = 10;

class World {
    private:
        WorldType worldType;
        std::vector<Block> blocks;
    public:
        World();
        World(WorldType worldType);
        WorldType getType();
        std::vector<Block> getBlocks();
        void addBlock(Block block);
};

#endif