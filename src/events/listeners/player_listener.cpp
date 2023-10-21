#include "events/listeners/player_listener.h"
#include "world/chunkmanager.h"
#include <iostream>

PlayerListener::PlayerListener() {

}

void PlayerListener::onBlockBreak(BlockBreakEvent* event) {
    ChunkManager chunkManager;
    Chunk* chunk = event->getChunk();
    int8_t block = event->getBlock();
    chunkManager.removeBlock(chunk, event->getBlockX(), event->getBlockY(), event->getBlockZ());
}

void PlayerListener::onBlockPlace(BlockPlaceEvent* event) {
    ChunkManager chunkManager;
    Chunk* chunk = event->getChunk();
    int8_t block = event->getBlock();
    chunkManager.addBlock(
        chunk, 
        event->getBlock(), 
        event->getBlockX() + event->getNormal().x,
        event->getBlockY() + event->getNormal().y,
        event->getBlockZ() + event->getNormal().z
    );
}