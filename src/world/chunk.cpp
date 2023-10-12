#include "world/chunk.h"
#include "world/world.h"
#include "game.h"
#include <iostream>

Chunk::Chunk() {

}

Chunk::~Chunk() {
    if (!this->outOfView()) return;
    for (int i = 0; i < CHUNK_SIZE; i++) {
        Block* block = blocks[i];
        if (block == nullptr) continue;
        delete block;
    }
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

bool Chunk::isEmpty() {
    return false;
}

bool Chunk::outOfView() {
    Player& player = Game::getInstance().getPlayer();
    int startX = std::max(0, int(player.getPosition().x / CHUNK_SIZE - Game::CHUNK_RENDER_DISTANCE));
    int startY = std::max(0, int(player.getPosition().y / CHUNK_SIZE - Game::CHUNK_RENDER_DISTANCE));
    int startZ = std::max(0, int(player.getPosition().z / CHUNK_SIZE - Game::CHUNK_RENDER_DISTANCE));

    int endX = player.getPosition().x / CHUNK_SIZE + Game::CHUNK_RENDER_DISTANCE;
    int endY = player.getPosition().y / CHUNK_SIZE + Game::CHUNK_RENDER_DISTANCE;
    int endZ = player.getPosition().z / CHUNK_SIZE + Game::CHUNK_RENDER_DISTANCE;
    return this->getX() < startX || this->getY() < startY || this->getZ() < startZ || this->getX() > endX || this->getY() > endY || this->getZ() > endZ;
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
    if (x * CHUNK_AREA + y * CHUNK_SIZE + z >= CHUNK_VOL || x < 0 || y < 0 || z < 0) return nullptr;
    return blocks[x * CHUNK_AREA + y * CHUNK_SIZE + z];
}
