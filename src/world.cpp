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


void World::addChunk(Chunk chunk) {
    chunks[chunk.getPosition().x][chunk.getPosition().y][chunk.getPosition().z] = chunk;
}
void World::addChunkMesh(ChunkMesh chunkMesh) {
    Chunk chunk = chunkMesh.getChunk();
    chunksMeshs[chunk.getPosition().x][chunk.getPosition().y][chunk.getPosition().z] = chunkMesh;
}