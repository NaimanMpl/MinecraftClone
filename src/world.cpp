#include "world.h"
#include <iostream>

World::World() { }

World::World(WorldType worldType, int width, int height) {
    this->worldType = worldType;
    World::width = width;
    World::height = height;
}

WorldType World::getType() {
    return this->worldType;
}

std::vector<Block> World::getBlocks() {
    return blocks;
}
int World::getWidth() {
    return width;
}

int World::getHeight() {
    return height;
}


void World::addBlock(Block block) {
    blocks.push_back(block);
}