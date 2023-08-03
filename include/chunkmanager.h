#ifndef CHUNKMANAGER_CLASS_H
#define CHUNKMANAGER_CLASS_H

#include "chunk.h"

class ChunkManager {

    public:
        ChunkManager();
        void removeBlock(Chunk* chunk, Block* block);
        void removeBlock(Chunk* chunk, int x, int y, int z);

        void addBlock(Chunk* chunk, int x, int y, int z, Material material);

};

#endif