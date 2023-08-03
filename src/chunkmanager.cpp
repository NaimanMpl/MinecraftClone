#include "chunkmanager.h"
#include "world.h"
#include "game.h"

ChunkManager::ChunkManager() {}

void ChunkManager::removeBlock(Chunk* chunk, Block* block) {
    Game& game = Game::getInstance();
    World& world = game.getWorld();

    chunk->setBlock(block->getX(), block->getY(), block->getZ(), nullptr);
    ChunkMesh* chunkMesh = world.getChunkMesh(chunk->getX(), chunk->getY(), chunk->getZ());

    chunkMesh->update(*chunk);
}

void ChunkManager::removeBlock(Chunk* chunk, int x, int y, int z) {

}

void ChunkManager::addBlock(Chunk* chunk, int x, int y, int z, Material material) {

}