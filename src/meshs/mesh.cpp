#include "mesh.h"

Mesh::Mesh() {
}

void Mesh::init() {

    shader = Shader("../assets/shaders/cubeShader.glsl", "../assets/shaders/cubeFragment.glsl");
    shader.enable();
    shader.setFloat("scale", 0.3f);

    VAO.bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) 0); // Coords
    VAO.linkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*) (3 * sizeof(float))); // Normals
    VAO.linkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*) (6 * sizeof(float))); // Textures

    VAO.unbind();
    VBO.unbind();
    EBO.unbind();
}

Shader& Mesh::getShader() {
    return shader;
}

void Mesh::draw() {
    VAO.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    VAO.unbind();
}

std::vector<GLuint>& Mesh::getIndices() {
    return indices;
}
std::vector<Vertex>& Mesh::getVertices() {
    return vertices;
}
