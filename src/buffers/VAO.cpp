#include "buffers/VAO.h"
#include <iostream>

void VAO::generate() {
    glGenVertexArrays(1, &ID);
}

void VAO::linkVBO(VBO VBO, GLuint layout) {
    VBO.bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glEnableVertexAttribArray(layout);
    VBO.unbind();
}

void VAO::linkAttrib(VBO VBO, GLuint layout, GLuint componentsSize, GLenum type, GLsizeiptr stride, void* offset) {
    VBO.bind();
    glVertexAttribPointer(layout, componentsSize, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.unbind();
}

GLuint* VAO::getID() {
    return &ID;
}

void VAO::bind() {
    glBindVertexArray(ID);
}

void VAO::unbind() {
    glBindVertexArray(0);
}

void VAO::destroy() {
    glDeleteVertexArrays(1, &ID);
}