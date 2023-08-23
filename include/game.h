#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include "world/world.h"
#include "camera.h"
#include "renderer.h"
#include "entity/player.h"
#include <thread>
#include "frustrum_culling.h"

class Game {

    private:
        World world;
        Camera camera;
        Player player;
        FrustrumCulling* frustrum;
        Game();
        void initWorld();
        void initTexture();
        void initListeners();
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
        void update(float deltaTime);
        World& getWorld();
        Camera& getCamera();
        Player& getPlayer();
};

#endif