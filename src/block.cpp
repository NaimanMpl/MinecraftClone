#include "block.h"
#include "shader.h"
#include <stb/stb_image.h>

Block::Block() {
    
}

Block::Block(Material material, double x, double y, double z) {
    this->material = material;
    this->x = x;
    this->y = y;
    this->z = z;
}

Material Block::getMaterial() {
    return this->material;
}

double Block::getX() {
    return this->x;
}

double Block::getY() {
    return this->y;
}

double Block::getZ() {
    return this->z;
}

void Block::setX(double x) {
    this->x = x;
}

void Block::setY(double y) {
    this->y = y;
}

void Block::setZ(double z) {
    this->z = z;
}