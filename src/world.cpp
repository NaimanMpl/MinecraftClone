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

std::vector<Chunk>& World::getChunks() {
    return chunks;
}

std::vector<ChunkMesh>& World::getChunksMeshs() {
    return chunksMeshs;
}
int World::getWidth() {
    return width;
}

int World::getHeight() {
    return height;
}


void World::addChunk(Chunk chunk, ChunkMesh chunkMesh) {
    chunks.push_back(chunk);
    chunksMeshs.push_back(chunkMesh);
}