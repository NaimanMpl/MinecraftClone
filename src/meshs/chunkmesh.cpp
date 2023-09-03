#include "meshs/chunkmesh.h"
#include "game.h"
#include "world/world.h"
#include "meshs/meshbuilder.h"

ChunkMesh::ChunkMesh() {

}

ChunkMesh::ChunkMesh(Chunk chunk) {
    this->chunk = chunk;
    vertices = MeshBuilder::buildChunkMesh(chunk);
    initMesh();
}

ChunkMesh::ChunkMesh(Chunk chunk, ChunkMeshData meshData) {
    this->chunk = chunk;
    vertices = meshData.vertices;
    initMesh();
}

void ChunkMesh::initMesh() {
    VAO.bind();

    VBO VBO(vertices);
    
    VAO.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) 0); // Coords
    VAO.linkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*) (3 * sizeof(float))); // Normals
    VAO.linkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*) (6 * sizeof(float))); // Textures
    VAO.linkAttrib(VBO, 3, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*) (8 * sizeof(float))); // voxelID
    VAO.linkAttrib(VBO, 4, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*) (9 * sizeof(float))); // faceID
    VAO.linkAttrib(VBO, 5, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*) (10 * sizeof(float))); // aoID

    VAO.unbind();
    VBO.unbind();
}

Chunk& ChunkMesh::getChunk() {
    return chunk;
}

void ChunkMesh::update(Chunk chunk) {
    this->chunk = chunk;
    vertices.clear();
    vertices = MeshBuilder::buildChunkMesh(chunk);
    initMesh();
}