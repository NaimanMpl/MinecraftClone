#include <glm/glm.hpp>
#include "ray.h"
#include "game.h"

Ray::Ray() {
    this->block = -1;
    this->chunk = nullptr;
    this->normal = glm::vec3(0.0f);
}

int8_t Ray::getBlock() {
    return this->block;
}

int Ray::getBlockX() {
    return this->blockX;
}

int Ray::getBlockY() {
    return this->blockY;
}

int Ray::getBlockZ() {
    return this->blockZ;
}

Chunk* Ray::getChunk() {
    return this->chunk;
}

glm::vec3 Ray::getNormal() {
    return this->normal;
}

void Ray::update() {
    Camera& camera = Game::getInstance().getCamera();
    World& world = Game::getInstance().getWorld();
    glm::vec3 start = camera.getPosition() + glm::vec3(0.0f, 0.5f, 0.0f);
    glm::vec3 end = start + camera.getFront() * 6.0f;

    glm::ivec3 rayPosition = glm::ivec3(start);

    float dx = glm::sign(end.x - start.x);
    float deltaX = dx != 0 ? std::min(dx / (end.x - start.x), 10000000.0f) : 10000000.0f;
    float tMaxX = dx > 0 ? deltaX * (1.0f - glm::fract(start.x)) : deltaX * glm::fract(start.x);

    float dy = glm::sign(end.y - start.y);
    float deltaY = dy != 0 ? std::min(dy / (end.y - start.y), 10000000.0f) : 10000000.0f;
    float tMaxY = dy > 0 ? deltaY * (1.0f - glm::fract(start.y)) : deltaY * glm::fract(start.y);

    float dz = glm::sign(end.z - start.z);
    float deltaZ = dz != 0 ? std::min(dz / (end.z - start.z), 10000000.0f) : 10000000.0f;
    float tMaxZ = dz > 0 ? deltaZ * (1.0f - glm::fract(start.z)) : deltaZ * glm::fract(start.z);
    int rayDirection = -1;

    this->normal = glm::vec3(0.0f);
    this->block = -1;

    while (tMaxX <= 1.0f || tMaxY <= 1.0f || tMaxZ <= 1.0f) {
        if (tMaxX < tMaxY && tMaxX < tMaxZ) {
            rayPosition.x += dx;
            tMaxX += deltaX;
            rayDirection = 0;
        } else if (tMaxY < tMaxX && tMaxY < tMaxZ) {
            rayPosition.y += dy;
            tMaxY += deltaY;
            rayDirection = 1;
        } else {
            rayPosition.z += dz;
            tMaxZ += deltaZ;
            rayDirection = 2;
        }

        int chunkX = rayPosition.x / CHUNK_SIZE;
        int chunkY = rayPosition.y / CHUNK_SIZE;
        int chunkZ = rayPosition.z / CHUNK_SIZE;

        Chunk* chunk = world.getChunk(chunkX, chunkY, chunkZ);

        if (chunk != nullptr) {
            
            int blockX = rayPosition.x % CHUNK_SIZE;
            int blockY = rayPosition.y % CHUNK_SIZE;
            int blockZ = rayPosition.z % CHUNK_SIZE;

            int8_t block = chunk->getBlock(blockX, blockY, blockZ);
            if (block != -1 && block != Material::WATER.getID()) {
                this->chunk = chunk;
                this->block = block;
                this->blockX = blockX;
                this->blockY = blockY;
                this->blockZ = blockZ;

                switch (rayDirection) {
                    case 0:
                        this->normal.x = -dx;
                        this->normal.y = 0.0f;
                        this->normal.z = 0.0f;
                        break;
                    case 1:
                        this->normal.x = 0.0f;
                        this->normal.y = -dy;
                        this->normal.z = 0.0f;
                        break;
                    case 2:
                        this->normal.x = 0.0f;
                        this->normal.y = 0.0f;
                        this->normal.z = -dz;
                        break;
                }

                break;
            }
        }
    }
}