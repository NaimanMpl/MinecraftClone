#ifndef BLOCK_BREAK_EVENT_H
#define BLOCK_BREAK_EVENT_H

#include "../player.h"
#include "../chunk.h"

class BlockBreakEvent {
    private:
        Chunk* chunk;
        Block* block;
        Player* player;
    public:
        BlockBreakEvent(Player* player, Chunk* chunk, Block* block);

        Player* getPlayer();
        Chunk* getChunk();
        Block* getBlock();
};

#endif