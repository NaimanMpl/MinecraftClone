#include "events/blockbreakevent.h"

BlockBreakEvent::BlockBreakEvent(Player* player, Chunk* chunk, Block* block) : player(player), chunk(chunk), block(block) {
    
}

Chunk* BlockBreakEvent::getChunk() {
    return this->chunk; 
}

Block* BlockBreakEvent::getBlock() {
    return this->block;
}

Player* BlockBreakEvent::getPlayer() {
    return this->player;
}