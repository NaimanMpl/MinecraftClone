#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include "../game_configuration.h"
#include "generator/terrain_generator.h"
#include "block.h"
#include "meshs/chunkmesh.h"
#include "meshs/watermesh.h"
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
        int8_t* blocks = nullptr;
        glm::ivec3 position;
        bool loaded = false;
        bool meshLoaded = false;
        ChunkMesh* mesh;
        WaterMesh* waterMesh;
        bool treeBuilt;
    public:
        int blocksSize;
        Chunk();
        Chunk(int x, int y, int z);

        glm::ivec3& getPosition();
        int getBlock(int x, int y, int z);
        int8_t* getBlocks();
        ChunkMesh* getMesh();
        WaterMesh* getWaterMesh();
        int getX();
        int getY();
        int getZ();
        bool isLoaded();
        bool isMeshLoaded();
        bool isEmpty();
        bool outOfView();
        bool hasTree();

        void setTreeBuilt(bool treeBuilt);
        void unload();
        void load(TerrainGenerator* terrainGenerator);
        void addBlock(int x, int y, int z, int8_t block);
        void setBlock(int x, int y, int z, int8_t block);
        void setMesh(ChunkMesh* mesh);
        void setWaterMesh(WaterMesh* waterMesh);
        void setMeshLoaded(bool loaded);
};

#endif