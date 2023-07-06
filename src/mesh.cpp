#include "mesh.h"

Mesh::Mesh() {
    
}

void Mesh::init() {

    VAO.bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) 0); // Coords
    VAO.linkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*) (3 * sizeof(float))); // Normals
    VAO.linkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*) (6 * sizeof(float))); // Textures

    VAO.unbind();
    VBO.unbind();
    EBO.unbind();
}