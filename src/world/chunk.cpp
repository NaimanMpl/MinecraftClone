#include "world/chunk.h"
#include "world/world.h"
#include "game.h"
#include <iostream>

Chunk::Chunk() {
}

Chunk::Chunk(int x, int y, int z) {
    this->position = glm::ivec3(x, y, z);
    blocks = new int8_t[CHUNK_VOL];
    for (int i = 0; i < CHUNK_VOL; i++) {
        blocks[i] = -1;
    }
    blocksSize = 0;
    mesh = nullptr;
    waterMesh = nullptr;
    doubleQuadMesh = nullptr;
    treeBuilt = false;
}

void Chunk::loadMeshes(ChunkMesh* chunkMesh, WaterMesh* waterMesh, DoubleQuadMesh* doubleQuadMesh) {
    if (!chunkMesh->getVertices().empty()) {
        this->setMesh(chunkMesh);
    } else {
        chunkMesh->unload();
        delete chunkMesh;
    }

    if (!waterMesh->getVertices().empty()) {
        this->setWaterMesh(waterMesh);
    } else {
        waterMesh->unload();
        delete waterMesh;
    }
    
    if (!doubleQuadMesh->getVertices().empty()) {
        this->setDoubleQuadMesh(doubleQuadMesh);
    } else {
        doubleQuadMesh->unload();
        delete doubleQuadMesh;
    }
    meshLoaded = true;
}

void Chunk::unload() {
    return;
    delete[] blocks;
    blocks = nullptr;
    blocksSize = 0;
    if (mesh != nullptr) {
        //mesh->unload();
        //delete mesh;
    }
    if (waterMesh != nullptr) {
        waterMesh->unload();
        delete waterMesh;
    }
    if (doubleQuadMesh != nullptr) {
        doubleQuadMesh->unload();
        delete doubleQuadMesh;
    }
    
}

void Chunk::load(TerrainGenerator* generator) {
    generator->generateTerrain(this);
    loaded = true;
}

glm::ivec3& Chunk::getPosition() {
    return this->position;
}

int8_t* Chunk::getBlocks() {
    return blocks;
}

ChunkMesh* Chunk::getMesh() {
    return this->mesh;
}

WaterMesh* Chunk::getWaterMesh() {
    return this->waterMesh;
}

DoubleQuadMesh* Chunk::getDoubleQuadMesh() {
    return this->doubleQuadMesh;
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
    return blocksSize == 0;
}

bool Chunk::outOfView() {
    Player& player = Game::getInstance().getPlayer();
    int startX = std::max(0, int(player.getPosition().x / CHUNK_SIZE - Game::CHUNK_RENDER_DISTANCE));
    int startZ = std::max(0, int(player.getPosition().z / CHUNK_SIZE - Game::CHUNK_RENDER_DISTANCE));

    int endX = player.getPosition().x / CHUNK_SIZE + Game::CHUNK_RENDER_DISTANCE;
    int endZ = player.getPosition().z / CHUNK_SIZE + Game::CHUNK_RENDER_DISTANCE;
    return this->getX() < startX || this->getZ() < startZ || this->getX() > endX || this->getZ() > endZ;
}

bool Chunk::hasTree() {
    return this->treeBuilt;
}

void Chunk::setTreeBuilt(bool treeBuilt) {
    this->treeBuilt = treeBuilt;
}

void Chunk::setMeshLoaded(bool loaded) {
    this->meshLoaded = loaded;
}

void Chunk::addBlock(int x, int y, int z, int8_t block) {
    blocksSize++;
    blocks[x * CHUNK_AREA + y * CHUNK_SIZE + z] = block;
}

void Chunk::setBlock(int x, int y, int z, int8_t block) {
    blocks[x * CHUNK_AREA + y * CHUNK_SIZE + z] = block;
}

void Chunk::setMesh(ChunkMesh* mesh) {
    this->mesh = mesh;
}

void Chunk::setWaterMesh(WaterMesh* waterMesh) {
    this->waterMesh = waterMesh;
}

void Chunk::setDoubleQuadMesh(DoubleQuadMesh* doubleQuadMesh) {
    this->doubleQuadMesh = doubleQuadMesh;
}

int Chunk::getBlock(int x, int y, int z) {
    if (x * CHUNK_AREA + y * CHUNK_SIZE + z >= CHUNK_VOL || x < 0 || y < 0 || z < 0) return -1;
    return blocks[x * CHUNK_AREA + y * CHUNK_SIZE + z];
}