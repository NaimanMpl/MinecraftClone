#include "meshs/imagemesh.h"

ImageMesh::ImageMesh() {}

ImageMesh::ImageMesh(int x, int y, float imageFormat, Shader& shader) {
    this->shader = shader;
    Vertex vertices[] = {
        Vertex{glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
        Vertex{glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
        Vertex{glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
        Vertex{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)}
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    ImageMesh::vertices.insert(ImageMesh::vertices.begin(), std::begin(vertices), std::end(vertices));
    ImageMesh::indices.insert(ImageMesh::indices.begin(), std::begin(indices), std::end(indices));

    init();
}