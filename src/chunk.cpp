#include "chunk.h"
#include <iostream>

Chunk::Chunk() {

}

Chunk::Chunk(int x, int y, int z) {
    this->position = glm::vec3(x, y, z);
    initBlocks();
}

void Chunk::initBlocks() {
    glm::ivec3 chunkWorldVector = glm::ivec3(position) * GameConfiguration::CHUNK_SIZE;
    int chunkX = chunkWorldVector.x;
    int chunkY = chunkWorldVector.y;
    int chunkZ = chunkWorldVector.z;
    for (unsigned int x = 0; x < GameConfiguration::CHUNK_SIZE; x++) {
        for (unsigned int z = 0; z < GameConfiguration::CHUNK_SIZE; z++) {
            int worldX = x + chunkX;
            int worldZ = z + chunkZ;
            float worldHeight = glm::simplex(glm::vec2(worldX, worldZ) / 64.0f);
            float localHeight = (worldHeight + 1) / 2;
            localHeight *= 32 + 32;
            std::cout << "Local Height : : " << localHeight << std::endl;
            for (unsigned int y = 0; y < int(localHeight); y++) {
                int worldY = y + chunkY;
                if (worldY + 1 == 0) continue;
                Block block(Material::BRICK, x, y, z);
                addBlock(block);
            }
        }
    }
}

std::vector<Block>& Chunk::getBlocks() {
    return this->blocks;
}

glm::ivec3& Chunk::getPosition() {
    return this->position;
}

void Chunk::addBlock(Block block) {
    blocks.push_back(block);
}