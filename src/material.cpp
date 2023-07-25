#include "material.h"

const Material Material::DIRT = Material(2, 0);
const Material Material::BRICK = Material(7, 0);
const Material Material::STONE = Material(1, 0);
const Material Material::SAND = Material(2, 1);
const Material Material::WOOD = Material(4, 0);
const Material Material::WOOL = Material(0, 4);
const Material Material::DIAMOND = Material(8, 1);

Material::Material() {

}

Material::Material(int x, int y) {
    this->x = x;
    this->y = y;
}

int Material::getX() {
    return this->x;
}

int Material::getY() {
    return this->y;
}
