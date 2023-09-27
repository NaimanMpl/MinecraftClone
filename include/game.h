#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include "world/world.h"
#include "camera.h"
#include "renderer.h"
#include "threadpool.h"
#include "entity/player.h"
#include "frustrum_culling.h"
#include "world/biome/biome.h"
#include <thread>
#include <mutex>
#include <tuple>
#include <map>
#include <queue>
#include <condition_variable>

struct UnloadedChunk {
    unsigned int x;
    unsigned int y;
    unsigned int z;
};

class Game {
    private:
        World world;
        Camera camera;
        Player player;
        FrustrumCulling* frustrum;
        std::mutex chunkQueueMutex;
        std::condition_variable conditionVariable;
        std::vector<std::thread> chunkLoadingThreads;
        std::vector<glm::ivec3> chunkToProcess;
        std::priority_queue<ChunkMeshData> unloadedChunks;
        ThreadPool* chunkLoadingThreadPool;
        bool running;
        Game();
        void initWorld();
        void initTexture();
        void initListeners();
        void loadChunks();
        const unsigned int CHUNK_RENDER_DISTANCE = 5;
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
        bool isRunning();
};

#endif