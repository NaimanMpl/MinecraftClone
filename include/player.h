#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include "ray.h"

class Player {
    private:
        bool canBreakBlock;
        Ray ray;
    public:
        Player();

        Ray& getRay();
        void update();
};

#endif