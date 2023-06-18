#ifndef BLOCK_CLASS_H
#define BLOCK_CLASS_H

#include <glad/glad.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include "buffers/VBO.h"
#include "buffers/EBO.h"
#include "texture.h"

class Block {
    private:
        glm::vec3 position;
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
        GLuint textureID, modelLocation, viewLocation, projectionLocation;
    public:
        Block(GLuint textureID, glm::vec3& position);
        glm::vec3 getPosition();
        glm::mat4 getModel();
        glm::mat4 getView();
        glm::mat4 getProjection();
        GLuint getTextureID();
};

#endif