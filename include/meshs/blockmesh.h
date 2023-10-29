#ifndef BLOCKMESH_CLASS_H
#define BLOCKMESH_CLASS_H

#include "mesh.h"

class BlockMesh : public Mesh {
    public:
        BlockMesh();
        
        void draw() override;
        void init() override;
        void unload() override;
};

#endif