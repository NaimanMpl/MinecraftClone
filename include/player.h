#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include "ray.h"
#include "events/playereventlistener.h"

class Player {
    private:
        bool canBreakBlock;
        std::vector<PlayerEventListener> listeners;
        Ray ray;
    public:
        Player();

        Ray& getRay();
        void update();
        void breakBlock(Chunk* chunk, Block* block);
        void addEventListener(PlayerEventListener listener);
};

#endif