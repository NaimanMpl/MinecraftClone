#include "meshs/blockiconmesh.h"
#include "meshs/meshbuilder.h"
#include "utils.h"

BlockIconMesh::BlockIconMesh() {
    vertices = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 1.0f,
        0.5f, 0.5f, 2.0f,
        0.5f, -0.5f, 3.0f
    };

    indices = {
        0, 1, 2,
        0, 2, 3
    };

    this->init();
}

void BlockIconMesh::init() {
    VAO.generate();
    VAO.bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.linkAttrib(VBO, 0, 2, GL_FLOAT, 3 * sizeof(float), (void*) 0);
    VAO.linkAttrib(VBO, 1, 1, GL_FLOAT, 3 * sizeof(float), (void*) (2 * sizeof(float)));

    VAO.unbind();
    VBO.unbind();
    EBO.unbind();
}

void BlockIconMesh::unload() {

}

void BlockIconMesh::draw() {
    
}

void BlockIconMesh::update(Shader shader, int8_t block) {
    
    Point point = Utils::getCubeTexCoordsFromBlock(block);
    glm::vec2 texCoords[4];
    texCoords[0] = glm::vec2((point.x * format) / width, ((height / format - 1.0f - point.y) * format) / height);
    texCoords[1] = glm::vec2((point.x * format) / width, ((height / format - 1.0f - point.y) * format) / height + format / height);
    texCoords[2] = glm::vec2((point.x * format) / width + format / width, ((height / format - 1.0f - point.y) * format) / height + format / height);
    texCoords[3] = glm::vec2((point.x * format) / width + format / width, ((height / format - 1.0f - point.y) * format) / height);

    glUniform2fv(glGetUniformLocation(shader.ID, "aTexture"), 4, &texCoords[0][0]);
}