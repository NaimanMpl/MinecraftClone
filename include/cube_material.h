#ifndef CUBE_MATERIAL_CLASS_H
#define CUBE_MATERIAL_CLASS_H

#include <unordered_map>
#include "material.h"
#include "buffers/VBO.h"

struct Point {
    unsigned int x;
    unsigned int y;
};

class CubeMaterial: public Material {
    private:
        std::unordered_map<BlockFace, Point> faces;
    public:
        static const CubeMaterial GRASS;
        CubeMaterial();
        CubeMaterial(std::string& name, std::unordered_map<BlockFace, Point>& faces);
        Point getTextureCoord(BlockFace faceID);
};

#endif