#include "world/material.h"

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

Material getCactusMaterial() {
    std::unordered_map<BlockFace, Point> faces;
    faces[BlockFace::LEFT] = Point{6, 4};
    faces[BlockFace::RIGHT] = Point{6, 4};
    faces[BlockFace::TOP] = Point{5, 4};
    faces[BlockFace::BOTTOM] = Point{7, 4};
    faces[BlockFace::FRONT] = Point{6, 4};
    faces[BlockFace::BACK] = Point{6, 4};
    std::string name("CACTUS");
    Material cactus = Material(99, name, faces);
    return cactus;
}

const Material Material::AIR = Material(-1, "AIR", -1, -1);
const Material Material::DIRT = Material(2, "DIRT", 2, 0);
const Material Material::BRICK = Material(7, "BRICK", 7, 0);
const Material Material::STONE = Material(1, "STONE", 1, 0);
const Material Material::SAND = Material(18, "SAND", 2, 1);
const Material Material::WOOD = Material(4, "WOOD", 4, 0);
const Material Material::WOOL = Material(64, "WOOL", 0, 4);
const Material Material::DIAMOND = Material(24, "DIAMOND", 8, 1);
const Material Material::WATER = Material(205, "WATER", 13, 12, false, false);
const Material Material::SNOW = Material(78, "SNOW", 2, 4);
const Material Material::LEAVE = Material(130, "LEAVE", 4, 8, true, true);
const Material Material::GRASS = getGrassMaterial();
const Material Material::OAK_WOOD = getOakWoodMaterial();
const Material Material::CACTUS = getCactusMaterial();

Material::Material() {

}

Material::Material(int id, std::string name, int x, int y) : Material(id, name, x, y, false, true) { }

Material::Material(int id, std::string name, int x, int y, bool transparent, bool solid) 
    : id(id), name(name), x(x), y(y), transparent(transparent), solid(solid), type(MaterialType::DEFAULT_MATERIAL) {
    std::unordered_map<BlockFace, Point> faces;
    faces[BlockFace::LEFT] = Point{6, 4};
    this->faces = faces;
}

Material::Material(int id, std::string name, std::unordered_map<BlockFace, Point>& faces) 
    : id(id), name(name), x(-1), y(-1), faces(faces), type(MaterialType::CUBE), transparent(false), solid(true) {
}

int Material::getX() {
    return this->x;
}

int Material::getY() {
    return this->y;
}

int Material::getID() {
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

bool Material::isTransparent() {
    return this->transparent;
}

bool Material::isSolid() {
    return this->solid;
}

