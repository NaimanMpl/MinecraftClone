#include "buffers/UBO.h"
#include <iostream>

UBO::UBO() {
    glGenBuffers(1, &ID);
    bind();
    // glBufferData(GL_UNIFORM_BUFFER, sizeof(Sprite), nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ID);
}

void UBO::bind() {
    glBindBuffer(GL_UNIFORM_BUFFER, ID);
}

void UBO::unbind() {
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UBO::destroy() {
    glDeleteBuffers(1, &ID);
}

GLuint UBO::getID() {
    return this->ID;
}