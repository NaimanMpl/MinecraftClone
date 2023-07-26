#include "chunk.h"
#include <iostream>

int k = 0;

Chunk::Chunk() {

}

Chunk::Chunk(int x, int y, int z) {
    this->position = glm::vec3(x, y, z);
    initBlocks();
    k++;
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
                Material material;
                switch (k) {
                    case 0:
                        material = Material::DIAMOND;
                        break;
                    case 1:
                        material = Material::SAND;
                        break;
                    case 2:
                        material = Material::BRICK;
                        break;
                    case 3:
                        material = Material::DIRT;
                        break;
                    case 4:
                        material = Material::WOOD;
                        break;
                    case 5:
                        material = Material::WOOL;
                        break;
                    default:
                        material = Material::STONE;
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

void Chunk::addBlock(Block* block) {
    blocks[block->getX() * CHUNK_AREA + block->getY() * CHUNK_SIZE + block->getZ()] = block;
}

Block* Chunk::getBlock(int x, int y, int z) {
    return blocks[x * CHUNK_AREA + y * CHUNK_SIZE + z];
}
