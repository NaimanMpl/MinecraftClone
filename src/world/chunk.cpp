#include "world/chunk.h"
#include "world/world.h"
#include "world/world_generator.h"
#include "game.h"
#include "treebuilder.h"
#include "perlinnoise.h"
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

    const int WATER_LEVEL = 40;
    const int SAND_LEVEL = 48;

    for (unsigned int x = 0; x < CHUNK_SIZE; x++) {
        for (unsigned int z = 0; z < CHUNK_SIZE; z++) {
            int worldX = x + chunkX;
            int worldZ = z + chunkZ;
            float biomeNoiseValue = WorldGenerator::getBiomeNoise(worldX, worldZ);
            Biome biome = WorldGenerator::determineBiome(biomeNoiseValue);
            float continentalness = WorldGenerator::getTerrainNoise(worldX, worldZ);
            int worldHeight = continentalness * 48 + 48;

            for (unsigned int y = 0; y < CHUNK_SIZE; y++) {
                int worldY = y + chunkY;
                Material material = Material::AIR;

                if (worldY < worldHeight) {
                    if (continentalness < 0) {
                        if (worldY < SAND_LEVEL) {
                            material = Material::SAND;
                        }
                    } else if (continentalness < 0.5f) {
                        if (worldY < worldHeight - 3) {
                            material = Material::STONE;
                        } else {
                            if (worldY > 55) {
                                material = Material::STONE;
                            } else {
                                material = Material::DIRT;
                            }
                        }
                    } else if (continentalness < 1.0f) {
                        material = Material::SNOW;
                    }
                } else if (worldY == worldHeight) {
                    if (0 <= continentalness && continentalness < 0.25f) {
                        material = Material::GRASS;
                    }
                }

                if (continentalness < -0.07f) {
                    if (worldY < WATER_LEVEL) {
                        material = Material::WATER;
                    }
                }

                if (material.getName() == "AIR") {
                    continue;
                } else if (material.getName() == "GRASS") {
                    if (rand() % 10 == 0) {
                        int trunkHeight = 3 + rand() % 3;
                        if (trunkHeight + y < CHUNK_SIZE && x + 4 < CHUNK_SIZE && z + 4 < CHUNK_SIZE) {
                            buildTree(this, x, z, trunkHeight, y);
                        }
                    }
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
    if (x * CHUNK_AREA + y * CHUNK_SIZE + z >= CHUNK_VOL) return nullptr;
    return blocks[x * CHUNK_AREA + y * CHUNK_SIZE + z];
}
