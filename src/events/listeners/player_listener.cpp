#include "events/listeners/player_listener.h"
#include "chunkmanager.h"
#include <iostream>

PlayerListener::PlayerListener() {

}

void PlayerListener::onBlockBreak(BlockBreakEvent* event) {
    ChunkManager chunkManager;
    Chunk* chunk = event->getChunk();
    Block* block = event->getBlock();
    chunkManager.removeBlock(chunk, block);
}