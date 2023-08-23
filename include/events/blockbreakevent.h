#ifndef BLOCK_BREAK_EVENT_CLASS_H
#define BLOCK_BREAK_EVENT_CLASS_H

class Player;
class Chunk;
class Block;

class BlockBreakEvent {
    private:
        Player* player;
        Chunk* chunk;
        Block* block;
    public:
        BlockBreakEvent(Player* player, Chunk* chunk, Block* block);

        Player* getPlayer();
        Chunk* getChunk();
        Block* getBlock();
};

#endif