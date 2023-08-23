#include "events/blockbreakevent.h"

BlockBreakEvent::BlockBreakEvent(Player* player, Chunk* chunk, Block* block) {
    this->player = player;
    this->block = block;
    this->chunk = chunk;
}

Player* BlockBreakEvent::getPlayer() {
    return this->player;
}

Chunk* BlockBreakEvent::getChunk() {
    return this->chunk;
}

Block* BlockBreakEvent::getBlock() {
    return this->block;
}