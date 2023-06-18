#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(const char* image, GLenum type, GLenum slot, GLenum format, GLenum pixelType) {
    this->type = type;
    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(type, ID);

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("../assets/textures/stone.png", &width, &height, &nrChannels, 0);
    
    if (data) {
        stbi_set_flip_vertically_on_load(false);
        glTexImage2D(type, 0, GL_RGBA, width, height, 0, format, pixelType, data);
        glGenerateMipmap(type);
    }

    stbi_image_free(data);
    glBindTexture(type, 0);
}

void Texture::texUnit(Shader shader, const char* uniform, GLuint unit) {
    GLuint tex0Uni = glGetUniformLocation(ID, uniform);
    shader.enable();
    glUniform1i(tex0Uni, 0);
}

void Texture::bind() {
    glBindTexture(type, ID);
}

void Texture::unbind() {
    glBindTexture(type, 0);
}

void Texture::destroy() {
    glDeleteTextures(1, &ID);
}