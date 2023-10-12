#ifndef WATERMESH_CLASS_H
#define WATERMESH_CLASS_H

#include <vector>
#include "mesh.h"

class WaterMesh: public Mesh {
    private:
        std::vector<float> vertices;
    public:
        WaterMesh();
        
};

#endif