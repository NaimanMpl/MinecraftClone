#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include "block.h"
#include "chunk.h"
#include "meshs/chunkmesh.h"
#include <vector>
#include "game_configuration.h"

enum WorldType { DEFAULT, FLAT };

static const int WORLD_WIDTH = 10;
static const int WORLD_HEIGHT = 3;
static const int WORLD_DEPTH = WORLD_WIDTH;

class World {
    private:
        WorldType worldType;
        Chunk chunks[WORLD_WIDTH][WORLD_HEIGHT][WORLD_DEPTH];
        ChunkMesh chunksMeshs[WORLD_WIDTH][WORLD_HEIGHT][WORLD_DEPTH];
        int width, height;
    public:
        World();
        World(WorldType worldType, int width, int height);

        WorldType getType();
        const Chunk (&getChunks() const)[WORLD_WIDTH][WORLD_HEIGHT][WORLD_DEPTH]{
            return chunks;
        }
        const ChunkMesh (&getChunksMeshs() const)[WORLD_WIDTH][WORLD_HEIGHT][WORLD_DEPTH] {
            return chunksMeshs;
        }
        int getWidth();
        int getHeight();

        void addChunk(Chunk chunk);
        void addChunkMesh(ChunkMesh chunkMesh);
};

#endif