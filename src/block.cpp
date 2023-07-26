#include "block.h"
#include "shader.h"
#include <stb/stb_image.h>

Block::Block() {
    
}

Block::Block(Material material, int x, int y, int z) {
    this->material = material;
    this->x = x;
    this->y = y;
    this->z = z;
}

Material Block::getMaterial() {
    return this->material;
}

int Block::getX() {
    return this->x;
}

int Block::getY() {
    return this->y;
}

int Block::getZ() {
    return this->z;
}

void Block::setX(int x) {
    this->x = x;
}

void Block::setY(int y) {
    this->y = y;
}

void Block::setZ(int z) {
    this->z = z;
}

void Block::toString() {
    std::cout << "Block(" << x << ", " << y << ", " << z << ")" << std::endl;
}