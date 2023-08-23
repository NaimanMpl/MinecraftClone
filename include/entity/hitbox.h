#ifndef HITBOX_H
#define HITBOX_H

#include "../world/block.h"

struct Point3D {
    float x;
    float y;
    float z;
};

class Hitbox {
    private:
        Point3D min;
        Point3D max;
    public:
        Hitbox();
        Hitbox(Point3D min, Point3D max);

        float getWidth();
        float getHeight();
        float getDepth();

        bool intersect(const Hitbox& other);
};

#endif