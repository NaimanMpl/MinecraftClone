#include "world/chunkmanager.h"
#include "world/world.h"
#include "meshs/meshbuilder.h"
#include "game.h"
#include "utils.h"

ChunkManager::ChunkManager() {}

void ChunkManager::removeBlock(Chunk* chunk, int x, int y, int z) {
    Game& game = Game::getInstance();
    World& world = game.getWorld();

    chunk->setBlock(x, y, z, -1);
    ChunkMesh* chunkMesh = chunk->getMesh();

    chunkMesh->update(chunk->getX(), chunk->getY(), chunk->getZ(), chunk->getBlocks());
}

void ChunkManager::addBlock(Chunk* chunk, int x, int y, int z, Material material) {

}

bool ChunkManager::outOfBounds(glm::ivec3 position) {
    if (position.x < 0 || position.y < 0 || position.z < 0) 
        return true;
    if (position.x + position.y * WORLD_AREA + position.z * WORLD_WIDTH >= WORLD_VOLUME)
        return true;
    return false;
}

Chunk* ChunkManager::loadChunk(int x, int y, int z) {
    World& world = Game::getInstance().getWorld();
    Chunk* chunk = new Chunk(x, y, z);
    chunk->load(world.getTerrainGenerator());
    return chunk;
}


ChunkMeshData ChunkManager::loadChunkMeshData(Chunk* chunk) {
    glm::vec3 chunkPosition(chunk->getX(), chunk->getY(), chunk->getZ());
    ChunkMeshData chunkMeshData{
        chunk->getX(), 
        chunk->getY(), 
        chunk->getZ(), 
        Utils::calculateDistance(chunkPosition * float(CHUNK_SIZE), Game::getInstance().getPlayer().getPosition())
    };
    chunkMeshData.vertices = MeshBuilder::buildChunkMesh(chunk->getX(), chunk->getY(), chunk->getZ(), chunk->getBlocks());
    return chunkMeshData;
}