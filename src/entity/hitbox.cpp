#include "entity/hitbox.h"

Hitbox::Hitbox() {}

Hitbox::Hitbox(Point3D min, Point3D max) {
    this->min = min;
    this->max = max;
}

float Hitbox::getWidth() {
    return std::abs(max.x - min.x);
}

float Hitbox::getHeight() {
    return std::abs(max.y - min.y);
}

float Hitbox::getDepth() {
    return std::abs(max.z - min.z);
}
