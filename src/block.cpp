#include "block.h"
#include "shader.h"
#include <stb/stb_image.h>

Block::Block(GLuint textureID, glm::vec3& position) {
    this->textureID = textureID;
    this->position = position;
    this->model = glm::mat4(1.0f);
    this->view = glm::mat4(1.0f);
    this->projection = glm::mat4(1.0f);
}

glm::vec3 Block::getPosition() {
    return this->position;
}

glm::mat4 Block::getModel() {
    return this->model;
}

glm::mat4 Block::getView() {
    return this->view;
}

glm::mat4 Block::getProjection() {
    return this->projection;
}

GLuint Block::getTextureID() {
    return this->textureID;
}