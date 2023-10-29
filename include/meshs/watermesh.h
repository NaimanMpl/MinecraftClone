#ifndef WATERMESH_CLASS_H
#define WATERMESH_CLASS_H

#include <vector>
#include <stdint.h>
#include "mesh.h"

class WaterMesh: public Mesh {
    private:
        std::vector<float> vertices;
        bool initiated;
    public:
        WaterMesh() = default;
        WaterMesh(int chunkX, int chunkY, int chunkZ, int8_t* blocks);

        std::vector<float>& getVertices();
        bool isInitiated();
        void init() override;
        void draw() override;
        void unload() override;
        
};

#endif