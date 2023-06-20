#include "world.h"
#include <iostream>

World::World() { }

World::World(WorldType worldType) {
    this->worldType = worldType;
}

WorldType World::getType() {
    return this->worldType;
}

std::vector<Block> World::getBlocks() {
    return blocks;
}

void World::addBlock(Block block) {
    blocks.push_back(block);
    std::cout << blocks.size() << std::endl;
}