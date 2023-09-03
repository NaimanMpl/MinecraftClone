#include "world/chunk.h"
#include "world/world.h"
#include <iostream>

Chunk::Chunk() {

}

Chunk::Chunk(int x, int y, int z) {
    this->position = glm::ivec3(x, y, z);
}

void Chunk::load(TerrainGenerator* generator) {
    generator->generateTerrain(this);
    loaded = true;
}

glm::ivec3& Chunk::getPosition() {
    return this->position;
}

Block** Chunk::getBlocks() {
    return blocks;
}

int Chunk::getX() {
    return position.x;
}

int Chunk::getY() {
    return position.y;
}

int Chunk::getZ() {
    return position.z;
}

bool Chunk::isLoaded() {
    return this->loaded;
}

bool Chunk::isMeshLoaded() {
    return this->meshLoaded;
}

void Chunk::setMeshLoaded(bool loaded) {
    this->meshLoaded = loaded;
}

void Chunk::addBlock(Block* block) {
    blocks[block->getX() * CHUNK_AREA + block->getY() * CHUNK_SIZE + block->getZ()] = block;
}

void Chunk::setBlock(int x, int y, int z, Block* block) {
    blocks[x * CHUNK_AREA + y * CHUNK_SIZE + z] = block;
}

Block* Chunk::getBlock(int x, int y, int z) {
    if (x * CHUNK_AREA + y * CHUNK_SIZE + z >= CHUNK_VOL) return nullptr;
    return blocks[x * CHUNK_AREA + y * CHUNK_SIZE + z];
}
