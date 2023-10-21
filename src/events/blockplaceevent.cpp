#include "events/blockplaceevent.h"

BlockPlaceEvent::BlockPlaceEvent(Chunk* chunk, int8_t block, int blockX, int blockY, int blockZ, glm::vec3 normal) {
    this->chunk = chunk;
    this->block = block;
    this->blockX = blockX;
    this->blockY = blockY;
    this->blockZ = blockZ;
    this->normal = normal;
}

Chunk* BlockPlaceEvent::getChunk() {
    return this->chunk;
}

int8_t BlockPlaceEvent::getBlock() {
    return this->block;
}

int BlockPlaceEvent::getBlockX() {
    return this->blockX;
}

int BlockPlaceEvent::getBlockY() {
    return this->blockY;
}

int BlockPlaceEvent::getBlockZ() {
    return this->blockZ;
}

glm::vec3& BlockPlaceEvent::getNormal() {
    return this->normal;
}