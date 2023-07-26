#include "material.h"

const Material Material::DIRT = Material("DIRT", 2, 0);
const Material Material::BRICK = Material("BRICK", 7, 0);
const Material Material::STONE = Material("STONE", 1, 0);
const Material Material::SAND = Material("SAND", 2, 1);
const Material Material::WOOD = Material("WOOD", 4, 0);
const Material Material::WOOL = Material("WOOL", 0, 4);
const Material Material::DIAMOND = Material("DIAMOND", 8, 1);

Material::Material() {

}

Material::Material(std::string name, int x, int y) {
    this->name = name;
    this->x = x;
    this->y = y;
    this->type = MaterialType::DEFAULT_MATERIAL;
}

int Material::getX() {
    return this->x;
}

int Material::getY() {
    return this->y;
}

std::string& Material::getName() {
    return this->name;
}

MaterialType Material::getType() {
    return this->type;
}
