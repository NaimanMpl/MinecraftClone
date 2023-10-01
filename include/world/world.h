#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include "block.h"
#include "chunk.h"
#include "../meshs/chunkmesh.h"
#include <vector>
#include <map>
#include "game_configuration.h"
#include "world/generator/default_world_generator.h"

enum WorldType { DEFAULT, FLAT };

static const int WORLD_WIDTH = 100;
static const int WORLD_HEIGHT = 10;
static const int WORLD_DEPTH = WORLD_WIDTH;
static const int WORLD_AREA = WORLD_WIDTH * WORLD_DEPTH;
static const int WORLD_VOLUME = WORLD_AREA * WORLD_HEIGHT;

class World {
    private:
        WorldType worldType;
        Chunk* chunks[WORLD_VOLUME] = {nullptr};
        ChunkMesh* chunksMeshs[WORLD_VOLUME] = {nullptr};
        std::vector<Point> trees;
        int width, height;
        uint8_t seed = 200;
        std::map<std::pair<int, int>, float> heightMap;
        TerrainGenerator* terrainGenerator;
    public:
        World();
        World(WorldType worldType);

        WorldType getType();
        Chunk** getChunks();
        ChunkMesh** getChunksMeshs();
        Chunk* getChunk(int x, int y, int z);
        Chunk* getChunkAt(unsigned int worldX, unsigned int worldY, unsigned int worldZ);
        Chunk* getChunkAt(glm::vec3 position);
        Block* getBlockAt(unsigned int worldX, unsigned int worldY, unsigned int worldZ);
        Block* getBlockAt(glm::vec3 position);
        ChunkMesh* getChunkMesh(int x, int y, int z);
        std::vector<Point>& getTrees();
        void addTree(Point tree);
        uint8_t getSeed();

        void addChunk(Chunk* chunk);
        void addChunkMesh(ChunkMesh* chunkMesh);
        TerrainGenerator* getTerrainGenerator();
};

#endif