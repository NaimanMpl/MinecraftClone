#ifndef DOUBLEQUAD_MESH_CLASS_H
#define DOUBLEQUAD_MESH_CLASS_H

#include "meshs/mesh.h"
#include <stdint.h>

class DoubleQuadMesh: public Mesh {
    private:
        std::vector<float> vertices;
        bool initiated;
    public:
        DoubleQuadMesh() = default;
        DoubleQuadMesh(int8_t* blocks);

        std::vector<float>& getVertices();
        bool isInitiated();
        void draw() override;
        void init() override;
        void unload() override;
};

#endif