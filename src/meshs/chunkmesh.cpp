#include "meshs/chunkmesh.h"
#include "game.h"
#include "world/world.h"
#include "meshs/meshbuilder.h"

ChunkMesh::ChunkMesh() {
}

ChunkMesh::ChunkMesh(int chunkX, int chunkY, int chunkZ, int8_t *blocks) {
    vertices = MeshBuilder::buildChunkMesh(chunkX, chunkY, chunkZ, blocks);
    this->init();
}

ChunkMesh::ChunkMesh(ChunkMeshData meshData) {
    vertices = meshData.vertices;
    // initMesh();
}

bool ChunkMesh::isMeshInitiated() {
    return this->meshInitiated;
}

void ChunkMesh::init() {
    VAO.generate();
    VAO.bind();

    VBO VBO(vertices);
    vboID = VBO.getID();

    VAO.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) 0);                           // Coords
    VAO.linkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*) (3 * sizeof(float)));         // Normals
    VAO.linkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*) (6 * sizeof(float)));         // Textures
    VAO.linkAttrib(VBO, 3, 1, GL_FLOAT, sizeof(Vertex), (void*) (8 * sizeof(float)));  // voxelID
    VAO.linkAttrib(VBO, 4, 1, GL_FLOAT, sizeof(Vertex), (void*) (9 * sizeof(float)));  // faceID
    VAO.linkAttrib(VBO, 5, 1, GL_FLOAT, sizeof(Vertex), (void*) (10 * sizeof(float))); // aoID

    VAO.unbind();
    VBO.unbind();
    meshInitiated = true;
}

void ChunkMesh::draw() {
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    VAO.unbind();
}

void ChunkMesh::update(int chunkX, int chunkY, int chunkZ, int8_t *blocks) {
    this->unload();
    vertices = MeshBuilder::buildChunkMesh(chunkX, chunkY, chunkZ, blocks);
    this->init();
}

void ChunkMesh::unload() {
    vertices.clear();
    vertices.shrink_to_fit();
    if (!this->isMeshInitiated())
        return;
    std::cout << "Je delete du buffer" << std::endl;
    glDeleteBuffers(1, vboID);
}