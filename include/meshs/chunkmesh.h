#ifndef CHUNKMESH_CLASS_H
#define CHUNKMESH_CLASS_H

#include "mesh.h"
#include "world/block.h"

struct ChunkMeshData {
    int x;
    int y;
    int z;
    float distance;
    std::vector<Vertex> vertices;

    bool operator<(const ChunkMeshData& other) const {
        return distance > other.distance;
    }
};

class ChunkMesh: public Mesh {
    private:
        bool meshInitiated = false;
    public:
        ChunkMesh();
        ChunkMesh(int chunkX, int chunkY, int chunkZ, int8_t* blocks);
        ChunkMesh(ChunkMeshData meshData);

        void init() override;
        void unload() override;
        void draw() override;
        bool isMeshInitiated();
        void update(int chunkX, int chunkY, int chunkZ, int8_t* blocks);
};

#endif