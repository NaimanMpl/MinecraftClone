#include "meshs/mesh.h"

Mesh::Mesh() {
}

Mesh::Mesh(Shader& shader, std::vector<Vertex>& vertices, std::vector<GLuint>& indices) {
    this->shader = shader;
    this->vertices = vertices;
    this->indices = indices;
}

Shader& Mesh::getShader() {
    return shader;
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
