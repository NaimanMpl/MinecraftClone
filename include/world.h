#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include "block.h"
#include "chunk.h"
#include "meshs/chunkmesh.h"
#include <vector>
#include "game_configuration.h"

enum WorldType { DEFAULT, FLAT };

static const int WORLD_WIDTH = 20;
static const int WORLD_HEIGHT = 3;
static const int WORLD_DEPTH = WORLD_WIDTH;
static const int WORLD_AREA = WORLD_WIDTH * WORLD_DEPTH;
static const int WORLD_VOLUME = WORLD_AREA * WORLD_DEPTH;

class World {
    private:
        WorldType worldType;
        Chunk* chunks[WORLD_VOLUME] = {nullptr};
        ChunkMesh* chunksMeshs[WORLD_VOLUME] = {nullptr};
        int width, height;
    public:
        World();
        World(WorldType worldType, int width, int height);

        WorldType getType();
        Chunk** getChunks();
        ChunkMesh** getChunksMeshs();
        Chunk* getChunk(int x, int y, int z);
        ChunkMesh* getChunkMesh(int x, int y, int z);
        int getWidth();
        int getHeight();

        void addChunk(Chunk* chunk);
        void addChunkMesh(ChunkMesh* chunkMesh);
};

#endif