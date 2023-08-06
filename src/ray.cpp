#include <glm/glm.hpp>
#include "ray.h"
#include "game.h"

Ray::Ray() {
    this->block = nullptr;
    this->chunk = nullptr;
}

Block* Ray::getBlock() {
    return this->block;
}

Chunk* Ray::getChunk() {
    return this->chunk;
}

void Ray::update() {
    Camera& camera = Game::getInstance().getCamera();
    World& world = Game::getInstance().getWorld();
    glm::vec3 start = camera.getPosition() + glm::vec3(0.5f, 0.5f, 0.5f);
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

    this->block = nullptr;

    while (tMaxX <= 1.0f || tMaxY <= 1.0f || tMaxZ <= 1.0f) {
        if (tMaxX < tMaxY && tMaxX < tMaxZ) {
            rayPosition.x += dx;
            tMaxX += deltaX;
        } else if (tMaxY < tMaxX && tMaxY < tMaxZ) {
            rayPosition.y += dy;
            tMaxY += deltaY;
        } else {
            rayPosition.z += dz;
            tMaxZ += deltaZ;
        }

        int chunkX = rayPosition.x / CHUNK_SIZE;
        int chunkY = rayPosition.y / CHUNK_SIZE;
        int chunkZ = rayPosition.z / CHUNK_SIZE;

        Chunk* chunk = world.getChunk(chunkX, chunkY, chunkZ);

        if (chunk != nullptr) {
            
            int blockX = rayPosition.x % CHUNK_SIZE;
            int blockY = rayPosition.y % CHUNK_SIZE;
            int blockZ = rayPosition.z % CHUNK_SIZE;

            Block* block = chunk->getBlock(blockX, blockY, blockZ);
            if (block != nullptr) {
                this->chunk = chunk;
                this->block = block;
                break;
            }
        }
    }
}