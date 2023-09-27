#include "meshs/handmesh.h"
#include "meshs/meshbuilder.h"

HandMesh::HandMesh() {
    shader = Shader("../assets/shaders/hand.vert", "../assets/shaders/hand.frag");
    vertices = MeshBuilder::buildHandMesh();
    indices = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };
    initMesh();
}

void HandMesh::initMesh() {
    VAO.bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) 0);
    VAO.linkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*) (3 * sizeof(float)));
    VAO.linkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*) (6 * sizeof(float)));

    VAO.unbind();
    VBO.unbind();
    EBO.unbind();
}