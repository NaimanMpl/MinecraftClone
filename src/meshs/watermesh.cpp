#include "meshs/watermesh.h"
#include "meshs/meshbuilder.h"
#include "utils.h"

WaterMesh::WaterMesh(int chunkX, int chunkY, int chunkZ, int8_t* blocks) {
    vertices = MeshBuilder::buildWaterMesh(chunkX, chunkY, chunkZ, blocks);
    initiated = false;
}

std::vector<float>& WaterMesh::getVertices() {
    return this->vertices;
}

bool WaterMesh::isInitiated() {
    return this->initiated;
}

void WaterMesh::init() {
    VAO.generate();
    VAO.bind();

    VBO VBO(vertices);
    vboID = VBO.getID();

    VAO.linkAttrib(VBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    VAO.linkAttrib(VBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));

    VAO.unbind();
    VBO.unbind();
    initiated = true;
}

void WaterMesh::unload() {
    vertices.clear();
    vertices.shrink_to_fit();
    if (!this->isInitiated()) return;
    glDeleteBuffers(1, vboID);
}

void WaterMesh::draw() {
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 5);
    VAO.unbind();
}

