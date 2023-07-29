#include "world.h"
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
    return chunks[x * WORLD_AREA + y * WORLD_WIDTH + z];
}

ChunkMesh* World::getChunkMesh(int x, int y, int z) {
    return chunksMeshs[x * WORLD_AREA + y * WORLD_WIDTH + z];
}

void World::addChunk(Chunk* chunk) {
    chunks[chunk->getPosition().x * WORLD_AREA + chunk->getPosition().y * WORLD_WIDTH + chunk->getPosition().z] = chunk;
}
void World::addChunkMesh(ChunkMesh* chunkMesh) {
    Chunk& chunk = chunkMesh->getChunk();
    chunksMeshs[chunk.getPosition().x * WORLD_AREA + chunk.getPosition().y * WORLD_WIDTH + chunk.getPosition().z] = chunkMesh;
}