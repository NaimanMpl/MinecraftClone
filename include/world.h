#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include "block.h"
#include "chunk.h"
#include "meshs/chunkmesh.h"
#include <vector>

enum WorldType { DEFAULT, FLAT };
static const int WORLD_WIDTH = 10;
static const int WORLD_HEIGHT = 10;

class World {
    private:
        WorldType worldType;
        std::vector<Chunk> chunks;
        std::vector<ChunkMesh> chunksMeshs;
        int width, height;
    public:
        World();
        World(WorldType worldType, int width, int height);

        WorldType getType();
        std::vector<Chunk>& getChunks();
        std::vector<ChunkMesh>& getChunksMeshs();
        int getWidth();
        int getHeight();

        void addChunk(Chunk chunk, ChunkMesh chunkMesh);
};

#endif