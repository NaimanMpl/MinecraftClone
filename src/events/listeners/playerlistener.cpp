#include "events/playerlistener.h"
#include "chunkmanager.h"

void PlayerListener::onBreakBlock(BlockBreakEvent* event) {
    ChunkManager chunkManager;
    Chunk* chunk = event->getChunk();
    Block* block = event->getBlock();
    chunkManager.removeBlock(chunk, block);
}