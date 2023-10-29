#ifndef HANDMESH_CLASS_H
#define HANDMESH_CLASS_H

#include "mesh.h"

class HandMesh: public Mesh {
    public:
        HandMesh();

        void draw() override;
        void init() override;
        void unload() override;
};

#endif