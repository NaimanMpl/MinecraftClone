#ifndef VERTICIES_CONSTANTS_H
#define VERTICIES_CONSTANTS_H

#include <glad/glad.h>

GLfloat BLOCK_VERTICES[] = {
    -1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, 1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, -1.0f,
    -1.0f, 1.0f, -1.0f,
};

GLuint BLOCK_INDICES[] = {
    1, 2, 6,
    6, 5, 1,
    0, 4, 7,
    7, 3, 0,
    4, 5, 7,
    6, 7, 4,
    0, 3, 2,
    2, 1, 0,
    0, 1, 5,
    5, 4, 0,
    3, 7, 6,
    6, 2, 3
};

#endif