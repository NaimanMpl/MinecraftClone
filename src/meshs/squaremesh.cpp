#include "meshs/squaremesh.h"

SquareMesh::SquareMesh(Point point, float width, float height, float format) {
    vertices = {
        -0.5f, -0.5f, point.x * format / width, (format - point.y * format) / height,
        -0.5f, 0.5f, point.x * format / width, (format - point.y * format) / height + format / height,
        0.5f, 0.5f, point.x * format / width + format / width, (format - point.y * format) / height + format / height,
        0.5f, -0.5f, point.x * format / width + format / width, (format - point.y * format) / height,
    };

    indices = {
        0, 1, 2,
        0, 2, 3
    };

    this->init();
}

void SquareMesh::init() {
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