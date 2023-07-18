#include "chunkmesh.h"

ChunkMesh::ChunkMesh() {
    ChunkMesh::shader = Shader("../assets/shaders/chunk.vert", "../assets/shaders/chunk.frag");
}