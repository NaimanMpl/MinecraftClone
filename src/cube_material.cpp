#include "cube_material.h"
#include <iostream>

CubeMaterial getGrassMaterial() {
    std::unordered_map<BlockFace, Point> faces;
    faces[BlockFace::LEFT] = Point{3, 0};
    faces[BlockFace::RIGHT] = Point{3, 0};
    faces[BlockFace::TOP] = Point{8, 2};
    faces[BlockFace::BOTTOM] = Point{2, 0};
    faces[BlockFace::FRONT] = Point{3, 0};
    faces[BlockFace::BACK] = Point{3, 0};
    std::string name("GRASS");
    CubeMaterial grass = CubeMaterial(name, faces);
    return grass;
}

const CubeMaterial CubeMaterial::GRASS = getGrassMaterial();

CubeMaterial::CubeMaterial() {}

CubeMaterial::CubeMaterial(std::string& name, std::unordered_map<BlockFace, Point>& faces) : Material(name, -1, -1) {
    this->faces = faces;
    this->type = MaterialType::CUBE;
}

Point CubeMaterial::getTextureCoord(BlockFace faceID) {
    return faces[faceID];  
}