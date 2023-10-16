#ifndef BLOCK_BREAK_EVENT_CLASS_H
#define BLOCK_BREAK_EVENT_CLASS_H

class Player;
class Chunk;
class Block;

#include <stdint.h>

class BlockBreakEvent {
    private:
        Player* player;
        Chunk* chunk;
        int8_t block;
        int blockX, blockY, blockZ;
    public:
        BlockBreakEvent(Player* player, Chunk* chunk, int8_t block, int blockX, int blockY, int blockZ);

        Player* getPlayer();
        Chunk* getChunk();
        int8_t getBlock();
        int getBlockX();
        int getBlockY();
        int getBlockZ();
};

#endif