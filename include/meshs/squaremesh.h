#ifndef SQUAREMESH_CLASS_H
#define SQUAREMESH_CLASS_H

#include "mesh.h"
#include "world/material.h"

class SquareMesh: public Mesh {
    private:
        std::vector<float> vertices;
    public:
        SquareMesh() = default;
        SquareMesh(Point point, float width, float height, float format);

        void init();
};

#endif