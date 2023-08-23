#include "world/world.h"
#include <iostream>

World::World() { }

World::World(WorldType worldType, int width, int height) {
    this->worldType = worldType;
    World::width = width;
    World::height = height;
}

WorldType World::getType() {
    return this->worldType;
}

int World::getWidth() {
    return width;
}

int World::getHeight() {
    return height;
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
    if (x * WORLD_AREA + y * WORLD_WIDTH + z >= WORLD_VOLUME) return nullptr;
    return chunks[x * WORLD_AREA + y * WORLD_WIDTH + z];
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
    if (x * WORLD_AREA + y * WORLD_WIDTH + z >= WORLD_VOLUME) return nullptr;
    return chunksMeshs[x * WORLD_AREA + y * WORLD_WIDTH + z];
}

void World::addChunk(Chunk* chunk) {
    chunks[chunk->getPosition().x * WORLD_AREA + chunk->getPosition().y * WORLD_WIDTH + chunk->getPosition().z] = chunk;
}
void World::addChunkMesh(ChunkMesh* chunkMesh) {
    Chunk& chunk = chunkMesh->getChunk();
    chunksMeshs[chunk.getPosition().x * WORLD_AREA + chunk.getPosition().y * WORLD_WIDTH + chunk.getPosition().z] = chunkMesh;
}