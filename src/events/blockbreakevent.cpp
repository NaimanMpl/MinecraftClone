#include "events/blockbreakevent.h"

BlockBreakEvent::BlockBreakEvent(Player* player, Chunk* chunk, int8_t block, int blockX, int blockY, int blockZ) {
    this->player = player;
    this->block = block;
    this->blockX = blockX;
    this->blockY = blockY;
    this->blockZ = blockZ;
    this->chunk = chunk;
}

Player* BlockBreakEvent::getPlayer() {
    return this->player;
}

Chunk* BlockBreakEvent::getChunk() {
    return this->chunk;
}

int8_t BlockBreakEvent::getBlock() {
    return this->block;
}

int BlockBreakEvent::getBlockX() {
    return this->blockX;
}

int BlockBreakEvent::getBlockY() {
    return this->blockY;
}

int BlockBreakEvent::getBlockZ() {
    return this->blockZ;
}