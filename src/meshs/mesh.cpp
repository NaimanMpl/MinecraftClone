#include "meshs/mesh.h"

Mesh::Mesh() {
}

Mesh::Mesh(Shader& shader, std::vector<Vertex>& vertices, std::vector<GLuint>& indices) {
    this->shader = shader;
    this->vertices = vertices;
    this->indices = indices;
    init();
}

void Mesh::init() {

    VAO.generate();
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

void Mesh::unload() {
    vertices.clear();
    indices.clear();

    vertices.shrink_to_fit();
    indices.shrink_to_fit();
}

void Mesh::draw() {
    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    VAO.unbind();
}

void Mesh::drawElements() {
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
