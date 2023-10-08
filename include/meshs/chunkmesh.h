#ifndef CHUNKMESH_CLASS_H
#define CHUNKMESH_CLASS_H

#include "mesh.h"
#include "world/chunk.h"
#include "utils.h"

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

struct ChunkMeshDataComparator {
    public:
        bool operator()(const std::pair<ChunkMeshData, Chunk*>& a, const std::pair<ChunkMeshData, Chunk*>& b) {
            return a.first.distance > b.first.distance;
        }
};

class ChunkMesh: public Mesh {
    private:
        Chunk chunk;
        bool meshInitiated = false;
    public:
        ChunkMesh();
        ChunkMesh(Chunk chunk);
        ChunkMesh(Chunk chunk, ChunkMeshData meshData);

        Chunk& getChunk();

        void initMesh();
        bool isMeshInitiated();
        void update(Chunk chunk);
};

#endif