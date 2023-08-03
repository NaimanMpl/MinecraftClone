#include "meshs/imagemesh.h"

ImageMesh::ImageMesh() {}

ImageMesh::ImageMesh(int x, int y, float imageFormat) {
    Vertex vertices[] = {
        Vertex{glm::vec3(-(0.125f / 4), (0.125f / 4), 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(x / imageFormat, y / imageFormat)},
        Vertex{glm::vec3((0.125f / 4), (0.125f / 4), 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(x / imageFormat, y / imageFormat + (1.0f / imageFormat))},
        Vertex{glm::vec3((0.125f / 4), -(0.125f / 4), 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(x / imageFormat + (1.0f / imageFormat), y / imageFormat + (1.0f / imageFormat))},
        Vertex{glm::vec3(-(0.125f / 4), -(0.125f / 4), 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(x / imageFormat, y / imageFormat + (1.0f / imageFormat))}
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    shader = Shader("../assets/shaders/default.vert", "../assets/shaders/default.frag");

    ImageMesh::vertices.insert(ImageMesh::vertices.begin(), std::begin(vertices), std::end(vertices));
    ImageMesh::indices.insert(ImageMesh::indices.begin(), std::begin(indices), std::end(indices));

    init();
}