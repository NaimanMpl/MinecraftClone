#ifndef CHUNKMESH_CLASS_H
#define CHUNKMESH_CLASS_H

#include "mesh.h"
#include "world/chunk.h"

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
        Chunk chunk;
        void initMesh();
    public:
        ChunkMesh();
        ChunkMesh(Chunk chunk);
        ChunkMesh(Chunk chunk, ChunkMeshData meshData);

        Chunk& getChunk();

        void update(Chunk chunk);
};

#endif