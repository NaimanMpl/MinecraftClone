#include "world/world.h"
#include <iostream>

World::World() { }

World::World(WorldType worldType) {
    this->worldType = worldType;
    this->terrainGenerator = new DefaultWorldGenerator();
}

WorldType World::getType() {
    return this->worldType;
}

uint8_t World::getSeed() {
    return this->seed;
}

Chunk** World::getChunks() {
    return chunks;
}
ChunkMesh** World::getChunksMeshs() {
    return chunksMeshs;
}

Chunk* World::getChunk(int x, int y, int z) {
    if (x + y * WORLD_AREA + z * WORLD_WIDTH >= WORLD_VOLUME || x < 0 || y < 0 || z < 0) return nullptr;
    return chunks[x + y * WORLD_AREA + z * WORLD_WIDTH];
}

Chunk* World::getChunkAt(unsigned int worldX, unsigned int worldY, unsigned int worldZ) {
    return this->getChunkAt(glm::vec3(worldX, worldY, worldZ));
}

Chunk* World::getChunkAt(glm::vec3 position) {
    int chunkX = position.x / CHUNK_SIZE;
    int chunkY = position.y / CHUNK_SIZE;
    int chunkZ = position.z / CHUNK_SIZE;

    return this->getChunk(chunkX, chunkY, chunkZ);
}

TerrainGenerator* World::getTerrainGenerator() {
    return this->terrainGenerator;
}

Block* World::getBlockAt(unsigned int worldX, unsigned int worldY, unsigned int worldZ) {
    return this->getBlockAt(glm::vec3(worldX, worldY, worldZ));
}

Block* World::getBlockAt(glm::vec3 position) {
    Chunk* chunk = getChunkAt(position);
    if (chunk == nullptr) return nullptr;
    int blockX = (int) position.x % CHUNK_SIZE;
    int blockY = (int) position.y % CHUNK_SIZE;
    int blockZ = (int) position.z % CHUNK_SIZE;

    return chunk->getBlock(blockX, blockY, blockZ);
}

ChunkMesh* World::getChunkMesh(int x, int y, int z) {
    if (x + y * WORLD_AREA + z * WORLD_WIDTH >= WORLD_VOLUME) return nullptr;
    return chunksMeshs[x + y * WORLD_AREA + z * WORLD_WIDTH];
}

void World::addChunk(Chunk* chunk) {
    chunks[chunk->getPosition().x + chunk->getPosition().y * WORLD_AREA + chunk->getPosition().z * WORLD_WIDTH] = chunk;
}

void World::addChunkMesh(ChunkMesh* chunkMesh) {
    Chunk& chunk = chunkMesh->getChunk();
    chunksMeshs[chunk.getPosition().x + chunk.getPosition().y * WORLD_AREA + chunk.getPosition().z * WORLD_WIDTH] = chunkMesh;
}