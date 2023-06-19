#ifndef VERTICES_CLASS_H
#define VERTICES_CLASS_H

#include <glad/glad.h>

namespace Vertices {

    GLfloat BLOCK_VERTICES[] = {
        // Face avant
        -0.5f, -0.5f, 0.5f,    0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,     1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,      1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f,     0.0f, 1.0f,

        // Face arrière
        -0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,     0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f,    1.0f, 1.0f,

        // Face gauche
        -0.5f, 0.5f, 0.5f,     1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,    0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,    1.0f, 1.0f,

        // Face droite
        0.5f, 0.5f, 0.5f,      0.0f, 0.0f,
        0.5f, 0.5f, -0.5f,     1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
        0.5f, -0.5f, 0.5f,     0.0f, 1.0f,

        // Face supérieure
        -0.5f, 0.5f, 0.5f,     0.0f, 1.0f,
        0.5f, 0.5f, 0.5f,      1.0f, 1.0f,
        0.5f, 0.5f, -0.5f,     1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,    0.0f, 0.0f,

        // Face inférieure
        -0.5f, -0.5f, 0.5f,    0.0f, 0.0f,
        0.5f, -0.5f, 0.5f,     1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f
    };

    GLuint BLOCK_INDICES[] = {
        // Face avant
        0, 1, 2,
        2, 3, 0,

        // Face arrière
        4, 5, 6,
        6, 7, 4,

        // Face gauche
        8, 9, 10,
        10, 11, 8,

        // Face droite
        12, 13, 14,
        14, 15, 12,

        // Face supérieure
        16, 17, 18,
        18, 19, 16,

        // Face inférieure
        20, 21, 22,
        22, 23, 20
    };

    GLfloat BLOCK_TEXTURE_COORDS[] = {
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    };
};

#endif