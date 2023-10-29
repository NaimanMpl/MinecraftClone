#include "meshs/doublequadmesh.h"
#include "meshs/meshbuilder.h"

DoubleQuadMesh::DoubleQuadMesh(int8_t* blocks) {
    vertices = MeshBuilder::buildQuadMesh(blocks);
    initiated = false;
}

std::vector<float>& DoubleQuadMesh::getVertices() {
    return this->vertices;
}

void DoubleQuadMesh::init() {
    VAO.generate();
    VAO.bind();

    VBO VBO(vertices);
    vboID = VBO.getID();

    VAO.linkAttrib(VBO, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*) 0);
    VAO.linkAttrib(VBO, 1, 2, GL_FLOAT, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    VAO.linkAttrib(VBO, 2, 1, GL_FLOAT, 6 * sizeof(float), (void*) (5 * sizeof(float)));

    VAO.unbind();
    VBO.unbind();

    initiated = true;
}

bool DoubleQuadMesh::isInitiated() {
    return this->initiated;
}

void DoubleQuadMesh::draw() {
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 5);
    VAO.unbind();
}

void DoubleQuadMesh::unload() {
    vertices.clear();
    vertices.shrink_to_fit();
    if (!this->isInitiated()) return;
    glDeleteBuffers(1, vboID);
}