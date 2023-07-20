#include "chunk.h"

Chunk::Chunk() {

}

Chunk::Chunk(std::vector<Block> blocks, glm::vec3 origin) {
    this->blocks = blocks;
    this->origin = origin;
}

std::vector<Block>& Chunk::getBlocks() {
    return this->blocks;
}

glm::vec3& Chunk::getOrigin() {
    return this->origin;
}

void Chunk::addBlock(Block block) {
    blocks.push_back(block);
}