#ifndef CHUNKMANAGER_CLASS_H
#define CHUNKMANAGER_CLASS_H

#include "world/chunk.h"
#include "world/world.h"
#include "meshs/chunkmesh.h"

class ChunkManager {

    public:
        ChunkManager();

        void removeBlock(Chunk* chunk, Block* block);
        void removeBlock(Chunk* chunk, int x, int y, int z);

        bool outOfBounds(glm::ivec3 position);
        void addBlock(Chunk* chunk, int x, int y, int z, Material material);
        Chunk* loadChunk(int x, int y, int z);
        ChunkMeshData loadChunkMeshData(Chunk* chunk);

};

#endif