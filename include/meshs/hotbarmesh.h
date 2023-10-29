#ifndef HOTBARMESH_CLASS_H
#define HOTBARMESH_CLASS_H

#include <vector>
#include "mesh.h"

class HotbarMesh: public Mesh {
    private:
        std::vector<float> vertices;
    public:
        HotbarMesh();

        void draw() override;
        void init() override;
        void unload() override;
};

#endif