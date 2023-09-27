#ifndef HANDMESH_CLASS_H
#define HANDMESH_CLASS_H

#include "mesh.h"

class HandMesh: public Mesh {
    private:
        void initMesh();
    public:
        HandMesh();
};

#endif