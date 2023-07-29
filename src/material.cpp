#include "material.h"

Material getGrassMaterial() {
    std::unordered_map<BlockFace, Point> faces;
    faces[BlockFace::LEFT] = Point{3, 0};
    faces[BlockFace::RIGHT] = Point{3, 0};
    faces[BlockFace::TOP] = Point{8, 2};
    faces[BlockFace::BOTTOM] = Point{2, 0};
    faces[BlockFace::FRONT] = Point{3, 0};
    faces[BlockFace::BACK] = Point{3, 0};
    std::string name("GRASS");
    Material grass = Material(3, name, faces);
    return grass;
}

Material getOakWoodMaterial() {
    std::unordered_map<BlockFace, Point> faces;
    faces[BlockFace::LEFT] = Point{4, 1};
    faces[BlockFace::RIGHT] = Point{4, 1};
    faces[BlockFace::TOP] = Point{5, 1};
    faces[BlockFace::BOTTOM] = Point{5, 1};
    faces[BlockFace::FRONT] = Point{4, 1};
    faces[BlockFace::BACK] = Point{4, 1};
    std::string name("OAK_WOOD");
    Material oakWood = Material(20, name, faces);
    return oakWood;
}

const Material Material::DIRT = Material(2, "DIRT", 2, 0);
const Material Material::BRICK = Material(7, "BRICK", 7, 0);
const Material Material::STONE = Material(1, "STONE", 1, 0);
const Material Material::SAND = Material(18, "SAND", 2, 1);
const Material Material::WOOD = Material(4, "WOOD", 4, 0);
const Material Material::WOOL = Material(64, "WOOL", 0, 4);
const Material Material::DIAMOND = Material(24, "DIAMOND", 8, 1);
const Material Material::WATER = Material(205, "DIAMOND", 13, 12);
const Material Material::GRASS = getGrassMaterial();
const Material Material::OAK_WOOD = getOakWoodMaterial();

Material::Material() {

}

Material::Material(unsigned int id, std::string name, int x, int y) {
    this->id = id;
    this->name = name;
    this->x = x;
    this->y = y;
    this->type = MaterialType::DEFAULT_MATERIAL;
}

Material::Material(unsigned int id, std::string name, std::unordered_map<BlockFace, Point>& faces) : Material(id, name, -1, -1) {
    this->type = MaterialType::CUBE;
    this->faces = faces;
}

int Material::getX() {
    return this->x;
}

int Material::getY() {
    return this->y;
}

unsigned int Material::getID() {
    return this->id;
}

std::string& Material::getName() {
    return this->name;
}

MaterialType Material::getType() {
    return this->type;
}

Point Material::getTextureCoord(BlockFace faceID) {
    return faces[faceID];  
}
