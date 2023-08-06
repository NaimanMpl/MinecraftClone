#ifndef IMAGEMESH_CLASS_H
#define IMAGEMESH_CLASS_H

#include "mesh.h"
#include "shader.h"

class ImageMesh : public Mesh {
    public:
        ImageMesh();
        ImageMesh(int x, int y, float imageFormat, Shader& shader);

        static const ImageMesh cursorMesh;
};

#endif