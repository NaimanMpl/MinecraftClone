#include "meshs/watermesh.h"

WaterMesh::WaterMesh() {
    vertices = {
        -0.5f, 0.5f, 0.0f, 13.0f / 16.0f, 12.0f / 16.0f,
        0.5f, 0.5f, 0.0f, 14.0f / 16.0f, 12.0f / 16.0f,
        0.5f, -0.5f, 0.0f, 14.0f / 16.0f, 13.0f / 16.0f,
        -0.5f, -0.5f, 0.0f, 13.0f / 16.0f, 13.0f / 16.0f
    };

    indices = {
        0, 1, 2,
        0, 2, 3
    };

    VAO.generate();
    VAO.bind();
    
    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.linkAttrib(VBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*) 0);
    VAO.linkAttrib(VBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*) (3 * sizeof(float)));

    VAO.unbind();
    VBO.unbind();
    EBO.unbind();
}