#ifndef BLOCK_PLACE_EVENT_CLASS_H
#define BLOCK_PLACE_EVENT_CLASS_H

#include <stdint.h>
#include <glm/glm.hpp>

class Player;
class Chunk;

class BlockPlaceEvent {
    private:
        int8_t block;
        Chunk* chunk;
        int blockX;
        int blockY;
        int blockZ;
        glm::vec3 normal;
    public:
        BlockPlaceEvent(Chunk* chunk, int8_t block, int blockX, int blockY, int blockZ, glm::vec3 normal);

        Chunk* getChunk();
        int8_t getBlock();

        int getBlockX();
        int getBlockY();
        int getBlockZ();

        glm::vec3& getNormal();
};

#endif