#ifndef HITBOX_H
#define HITBOX_H

#include "../world/block.h"

struct Point3D {
    float x;
    float y;
    float z;
};

class Hitbox {
    public:
        Point3D min;
        Point3D max;
        Hitbox();
        Hitbox(Point3D min, Point3D max);

        float getWidth();
        float getHeight();
        float getDepth();

        bool intersect(int x, int y, int z);
};

#endif