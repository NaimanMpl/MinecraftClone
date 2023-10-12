#include "meshs/hotbarmesh.h"

HotbarMesh::HotbarMesh() {
    vertices = {
        -3.0f, 0.5f, 0.0f, 0.0f,
        3.0f, 0.5f, 1.0f, 0.0f,
        3.0f, -0.5f, 1.0f, 22.0f / 46.0f,
        -3.0f, -0.5f, 0.0f, 22.0f / 46.0f
    };
    
    indices = {
        0, 1, 2,
        0, 2, 3
    };

    VAO.generate();
    VAO.bind();

    VBO VBO(vertices);
    EBO EBO(indices);

    VAO.linkAttrib(VBO, 0, 2, GL_FLOAT, 4 * sizeof(float), (void*) 0);
    VAO.linkAttrib(VBO, 1, 2, GL_FLOAT, 4 * sizeof(float), (void*) (2 * sizeof(float)));

    VAO.unbind();
    VBO.unbind();
    EBO.unbind();
}