#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include "world.h"
#include "camera.h"

class Game {

    private:
        World world;
        Camera camera;
        Game();
        void initWorld();
        void initTexture();
    public:
        static Game& getInstance() {
            static Game instance;
            return instance;
        }

        Game(const Game&) = delete;
        
        void operator=(const Game&) = delete;

        void init();
        void quit();
        World getWorld();
        Camera getCamera();

};

#endif