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
#include <set>
#include <queue>
#include <condition_variable>

constexpr int UPDATES_PER_SECONDS = 200;
constexpr double UPDATE_DELAY = 1.0 / UPDATES_PER_SECONDS;

struct UnloadedChunk {
    unsigned int x;
    unsigned int y;
    unsigned int z;
};

struct ChunkCoordsComparator {
    bool operator()(const glm::ivec3& a, const glm::ivec3& b) const {
        if(a.x != b.x) return a.x < b.x;
        if(a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    }
};

class Game {
    private:
        World world;
        Camera camera;
        Player player;
        FrustrumCulling* frustrum;
        std::mutex chunkQueueMutex;
        std::mutex chunkRemoveMutex;
        std::vector<std::thread> chunkLoadingThreads;
        std::vector<ChunkCoordinates> chunksToRemove;
        std::set<glm::ivec3, ChunkCoordsComparator> previousLoadedChunks;
        std::set<glm::ivec3, ChunkCoordsComparator> currentLoadedChunks;
        ThreadPool* chunkLoadingThreadPool;
        std::condition_variable conditionVariable;
        float elapsedTime;
        float updateTimer;
        double currentTickTime;
        double lastTickTime;
        bool running;
        bool chunkNeedToBeRemoved;
        Game();
        void initListeners();
        void loadChunks();
        void unloadChunks();
        void updateGameLogic();
    public:
        static const unsigned int CHUNK_RENDER_DISTANCE = 8;
        static const double TICK_RATE;
        static const double TICK_INTERVAL;
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
        void updateTick();
        World& getWorld();
        Camera& getCamera();
        Player& getPlayer();
        float getElapsedTime();
        bool isRunning();
        void setUpdateTimer(float time);
        float getUpdateTimer();
};

#endif