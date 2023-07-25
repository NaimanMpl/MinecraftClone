#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include "world.h"
#include "camera.h"
#include "renderer.h"
#include <thread>

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
        void render(Renderer& renderer);
        void update();
        World& getWorld();
        Camera& getCamera();
};

#endif