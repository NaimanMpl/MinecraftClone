#include "chunk.h"
#include "world.h"
#include "game.h"
#include "treebuilder.h"
#include <iostream>

Chunk::Chunk() {

}

Chunk::Chunk(int x, int y, int z) {
    this->position = glm::ivec3(x, y, z);
    initBlocks();
}

void Chunk::initBlocks() {
    glm::ivec3 chunkWorldVector = glm::ivec3(position) * CHUNK_SIZE;
    int chunkX = chunkWorldVector.x;
    int chunkY = chunkWorldVector.y;
    int chunkZ = chunkWorldVector.z;
    for (unsigned int x = 0; x < CHUNK_SIZE; x++) {
        for (unsigned int z = 0; z < CHUNK_SIZE; z++) {
            int worldX = x + chunkX;
            int worldZ = z + chunkZ;
            int worldHeight = int(glm::simplex(glm::vec2(worldX, worldZ) / 64.0f) * 32 + 32);
            int localHeight = std::min(worldHeight - chunkY, CHUNK_SIZE);
            if (localHeight <= 0) continue;
            // std::cout << "Local Height : " << localHeight << std::endl;
            for (unsigned int y = 0; y < localHeight; y++) {
                int worldY = y + chunkY;
                float textureNoise = glm::simplex(glm::vec2(worldX, worldZ) / 64.0f);
                Material material;
                if (textureNoise < 0.1) {
                    material = Material::WATER;
                } else if (textureNoise < 0.3) {
                    material = Material::SAND;
                } else if (textureNoise < 0.6) {
                    material = Material::GRASS;
                } else if (textureNoise < 0.8) {
                    material = Material::STONE;
                } else {
                    material = Material::SNOW;
                }
                Block* block = new Block(material, x, y, z);
                addBlock(block);
            }
        }
    }
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

void Chunk::addBlock(Block* block) {
    blocks[block->getX() * CHUNK_AREA + block->getY() * CHUNK_SIZE + block->getZ()] = block;
}

void Chunk::setBlock(int x, int y, int z, Block* block) {
    blocks[x * CHUNK_AREA + y * CHUNK_SIZE + z] = block;
}

float Chunk::noise2D(int8_t x, int8_t z, float size, float height, float shift) {
    World& world = Game::getInstance().getWorld();
    return glm::simplex(glm::vec2(float(world.getSeed() + shift + position.x + x) / size, float(world.getSeed() + shift + position.x + x) / size)) * height;
}

Block* Chunk::getBlock(int x, int y, int z) {
    return blocks[x * CHUNK_AREA + y * CHUNK_SIZE + z];
}
