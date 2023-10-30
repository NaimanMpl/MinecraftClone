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
    Material grass = Material(10, name, faces);
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
    Material oakWood = Material(11, name, faces);
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
    Material cactus = Material(12, name, faces);
    return cactus;
}

Material getBirchWoordMaterial() {
    std::unordered_map<BlockFace, Point> faces;
    faces[BlockFace::LEFT] = Point{5, 7};
    faces[BlockFace::RIGHT] = Point{5, 7};
    faces[BlockFace::TOP] = Point{5, 1};
    faces[BlockFace::BOTTOM] = Point{5, 1};
    faces[BlockFace::FRONT] = Point{5, 7};
    faces[BlockFace::BACK] = Point{5, 7};
    std::string name("OAK_WOOD");
    Material birchWood = Material(16, name, faces);
    return birchWood;
}

Material Material::AIR = Material(-1, "AIR", -1, -1);
Material Material::DIRT = Material(0, "DIRT", 2, 0);
Material Material::BRICK = Material(1, "BRICK", 7, 0);
Material Material::STONE = Material(2, "STONE", 1, 0);
Material Material::SAND = Material(3, "SAND", 2, 1);
Material Material::WOOD = Material(4, "WOOD", 4, 0);
Material Material::WOOL = Material(5, "WOOL", 0, 4);
Material Material::DIAMOND = Material(6, "DIAMOND", 8, 1);
Material Material::WATER = Material(7, "WATER", 13, 12, true, false);
Material Material::SNOW = Material(8, "SNOW", 2, 4);
Material Material::LEAVE = Material(9, "LEAVE", 4, 8, true, true);
Material Material::GRASS = getGrassMaterial();
Material Material::OAK_WOOD = getOakWoodMaterial();
Material Material::BIRCH_WOOD = getBirchWoordMaterial();
Material Material::CACTUS = getCactusMaterial();
Material Material::GRASS_ITEM = Material(13, MaterialType::QUAD, "GRASS ITEM", 7, 2, true, false);
Material Material::RED_FLOWER = Material(14, MaterialType::QUAD, "Red Flower", 12, 0, true, false);
Material Material::YELLOW_FLOWER = Material(15, MaterialType::QUAD, "Yellow Flower", 13, 0, true, false);

Material::Material() {

}

Material::Material(int id, std::string name, int x, int y) : Material(id, name, x, y, false, true) { }

Material::Material(int id, std::string name, int x, int y, bool transparent, bool solid) 
    : id(id), name(name), x(x), y(y), transparent(transparent), solid(solid), type(MaterialType::DEFAULT_MATERIAL) {
    std::unordered_map<BlockFace, Point> faces;
    faces[BlockFace::LEFT] = Point{6, 4};
    this->faces = faces;
}

Material::Material(int id, MaterialType type, std::string name, int x, int y, bool transparent, bool solid) 
    : id(id), type(type), name(name), x(x), y(y), transparent(transparent), solid(solid) {
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