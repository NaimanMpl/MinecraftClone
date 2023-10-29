#ifndef BLOCKICON_MESH_H
#define BLOCKICON_MESH_H

#include "mesh.h"

class BlockIconMesh: public Mesh {
    private:
        std::vector<float> vertices;
        float format = 32.0f;
        float width = 512.0f;
        float height = width;
    public:
        BlockIconMesh();

        void update(Shader shader, int8_t block);
        void init() override;
        void unload() override;
        void draw() override;
};

#endif