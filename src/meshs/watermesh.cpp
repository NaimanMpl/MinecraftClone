#include "meshs/watermesh.h"
#include "meshs/meshbuilder.h"

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

    VAO.linkAttrib(VBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    VAO.linkAttrib(VBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));

    VAO.unbind();
    VBO.unbind();
    initiated = true;
}

void WaterMesh::draw() {
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    VAO.unbind();
}

