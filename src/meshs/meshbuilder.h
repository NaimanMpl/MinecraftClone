#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include <vector>
#include "mesh.h"
#include "game_configuration.h"

class MeshBuilder {
    public:
        static std::vector<Vertex> buildChunkMesh(float* voxels);
};

#endif