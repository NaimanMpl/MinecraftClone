#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include "../game_configuration.h"
#include "generator/terrain_generator.h"
#include "block.h"
#include "meshs/chunkmesh.h"
#include <glm/gtc/noise.hpp>

const int CHUNK_SIZE = 16;
const int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
const int CHUNK_VOL = CHUNK_AREA * CHUNK_SIZE;
const int CHUNK_SPHERE_RADIUS = CHUNK_SIZE * sqrt(3) / 2;

struct ChunkCoordinates {
    int x;
    int y;
    int z;

    bool operator==(const ChunkCoordinates& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct ChunkCoordinatesHash {
    size_t operator()(const ChunkCoordinates& coordinates) const {
        size_t xHash = std::hash<int>{}(coordinates.x);
        size_t yHash = std::hash<int>{}(coordinates.y);
        size_t zHash = std::hash<int>{}(coordinates.z);

        return xHash ^ (yHash << 1) ^ (zHash << 2);
    }
};

class Chunk {
    private:
        Block** blocks = nullptr;
        glm::ivec3 position;
        bool loaded = false;
        bool meshLoaded = false;
        ChunkMesh* mesh;
    public:
        int blocksSize;
        Chunk();
        Chunk(int x, int y, int z);

        glm::ivec3& getPosition();
        Block* getBlock(int x, int y, int z);
        Block** getBlocks();
        ChunkMesh* getMesh();
        int getX();
        int getY();
        int getZ();
        bool isLoaded();
        bool isMeshLoaded();
        bool isEmpty();
        bool outOfView();

        void unload();
        void load(TerrainGenerator* terrainGenerator);
        void addBlock(Block* block);
        void setBlock(int x, int y, int z, Block* block);
        void setMesh(ChunkMesh* mesh);
        void setMeshLoaded(bool loaded);
};

#endif