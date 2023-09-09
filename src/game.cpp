#include <glm/gtc/matrix_transform.hpp>
#include "game.h"
#include "texture.h"
#include "game_configuration.h"
#include "events/listeners/player_listener.h"
#include "world/generator/default_world_generator.h"
#include <thread>
#include <chrono>
#include "meshs/meshbuilder.h"
#include "world/chunkmanager.h"

Texture stoneTexture("../assets/textures/stone.png");    
Texture brickTexture("../assets/textures/brick.png");
Texture grassTexture("../assets/textures/sand.png");

Game::Game() {
    
}

void Game::init() {
    running = true;
    world = World(WorldType::DEFAULT);
    glm::vec3 playerPosition = glm::vec3(int(WORLD_WIDTH * CHUNK_SIZE / 2) + 200, int(WORLD_HEIGHT * CHUNK_SIZE / 2), int(WORLD_DEPTH * CHUNK_SIZE / 2) + 200);
    player = Player(playerPosition);
    camera = Camera(GameConfiguration::WINDOW_WIDTH, GameConfiguration::WINDOW_HEIGHT, playerPosition);
    frustrum = new FrustrumCulling(&camera);
    initListeners();
    initTexture();
    // initWorld();
    chunkLoadingThreadPool = new ThreadPool(pow(CHUNK_RENDER_DISTANCE, 2));
    chunkLoadingThreads.emplace_back([this]() { 
        this->loadChunks();
    });
}

void Game::initListeners() {
    player.addEventListener(new PlayerListener());
}

void Game::initTexture() {
}

void Game::initWorld() {

    unsigned int startX = std::max(0, int(player.getPosition().x / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));
    unsigned int startY = std::max(0, int(player.getPosition().y / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));
    unsigned int startZ = std::max(0, int(player.getPosition().z / CHUNK_SIZE - 1));

    unsigned int endX = std::min(WORLD_WIDTH, int(player.getPosition().x / CHUNK_SIZE + CHUNK_RENDER_DISTANCE));
    unsigned int endY = std::min(WORLD_HEIGHT, int(player.getPosition().y / CHUNK_SIZE + CHUNK_RENDER_DISTANCE));
    unsigned int endZ = std::min(WORLD_DEPTH, int(player.getPosition().z / CHUNK_SIZE + (camera.getFront().z > 0 ? -1 : 1) * CHUNK_RENDER_DISTANCE));

    for (unsigned int x = startX; x < endX; x++) {
        for (unsigned int y = startY; y < endY; y++) {
            for (unsigned int z = startZ; z < endZ; z++) {
                Chunk* chunk = new Chunk(x, y, z);
                chunk->load(world.getTerrainGenerator());
                world.addChunk(chunk);
            }
        }
    }
    for (unsigned int x = startX; x < endX; x++) {
        for (unsigned int y = startY; y < endY; y++) {
            for (unsigned int z = startZ; z < endZ; z++) {
                Chunk* chunk = world.getChunk(x, y, z);
                ChunkMesh* chunkMesh = new ChunkMesh(*chunk);
                world.addChunkMesh(chunkMesh);
            }
        }
    }
    std::cout << "Le monde a été correctement initié !" << std::endl;
}

bool exists(std::vector<glm::ivec3> array, glm::ivec3 vector) {
    for (int i = 0; i < array.size(); i++) {
        glm::ivec3 position = array[i];
        if (position.x == vector.x && position.y == vector.y && position.z == vector.z) {
            return true;
        }
    }
    return false;
}

void Game::loadChunks() {
    std::vector<glm::ivec3> chunkAlreadyInQueue;
    while (true) {

        int startX = std::max(0, int(player.getPosition().x / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));
        int startY = std::max(0, int(player.getPosition().y / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));
        int startZ = std::max(0, int(player.getPosition().z / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));

        int endX = std::min(WORLD_WIDTH, int(player.getPosition().x / CHUNK_SIZE + CHUNK_RENDER_DISTANCE));
        int endY = std::min(WORLD_HEIGHT, int(player.getPosition().y / CHUNK_SIZE + CHUNK_RENDER_DISTANCE));
        int endZ = std::min(WORLD_DEPTH, int(player.getPosition().z / CHUNK_SIZE + CHUNK_RENDER_DISTANCE));
        
        for (int x = startX; x < endX; x++) {
            for (int y = startY; y < endY; y++) {
                for (int z = startZ; z < endZ; z++) {
                    if (chunkLoadingThreadPool->getCurrentTasksSize() + 1 > chunkLoadingThreadPool->getThreadsSize()) continue;
                    chunkLoadingThreadPool->enqueue([&] {
                        auto start = std::chrono::high_resolution_clock::now();
                        std::vector<glm::ivec3> adjacentChunksPositions;
                        adjacentChunksPositions.push_back(glm::vec3(x, y, z));
                        /*
                        adjacentChunksPositions.push_back(glm::vec3(x + 1, y, z));
                        adjacentChunksPositions.push_back(glm::vec3(x - 1, y, z));
                        adjacentChunksPositions.push_back(glm::vec3(x, y + 1, z));
                        adjacentChunksPositions.push_back(glm::vec3(x, y - 1, z));
                        adjacentChunksPositions.push_back(glm::vec3(x, y, z + 1));
                        adjacentChunksPositions.push_back(glm::vec3(x, y, z - 1));
                        */
                        ChunkManager chunkManager;
                        for (glm::ivec3& chunkPosition : adjacentChunksPositions) {
                            if (chunkManager.outOfBounds(chunkPosition)) continue;
                            if (exists(chunkToProcess, chunkPosition)) continue;
                            chunkToProcess.push_back(chunkPosition);
                            Chunk* chunk = world.getChunk(chunkPosition.x, chunkPosition.y, chunkPosition.z);
                            if (chunk == nullptr)
                                chunk = chunkManager.loadChunk(chunkPosition.x, chunkPosition.y, chunkPosition.z);
                            ChunkMeshData chunkMeshData = chunkManager.loadChunkMeshData(chunk);
                            std::unique_lock<std::mutex> lock(chunkQueueMutex);
                            unloadedChunks.push(chunkMeshData);
                        }
                        auto stop = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                    });
                }
            }
        }
    }
}

void Game::render(Renderer& renderer) {

    if (!unloadedChunks.empty()) {
        std::unique_lock<std::mutex> lock(chunkQueueMutex);
        ChunkMeshData chunkMeshData = unloadedChunks.top();
        unloadedChunks.pop();
        Chunk* chunk = world.getChunk(chunkMeshData.x, chunkMeshData.y, chunkMeshData.z);
        ChunkMesh* chunkMesh = world.getChunkMesh(chunkMeshData.x, chunkMeshData.y, chunkMeshData.z);
        if (chunkMesh == nullptr) {
            chunkMesh = new ChunkMesh(*chunk, chunkMeshData);
            world.addChunkMesh(chunkMesh);
        }
    }
    int startX = std::max(0, int(player.getPosition().x / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));
    int startY = std::max(0, int(player.getPosition().y / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));
    int startZ = std::max(0, int(player.getPosition().z / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));

    int endX = std::min(WORLD_WIDTH, int(player.getPosition().x / CHUNK_SIZE + CHUNK_RENDER_DISTANCE));
    int endY = std::min(WORLD_HEIGHT, int(player.getPosition().y / CHUNK_SIZE + CHUNK_RENDER_DISTANCE));
    int endZ = std::min(WORLD_DEPTH, int(player.getPosition().z / CHUNK_SIZE + CHUNK_RENDER_DISTANCE));

    for (int x = startX; x < endX; x++) {
        for (int y = startY; y < endY; y++) {
            for (int z = startZ; z < endZ; z++) {
                Chunk* chunk = world.getChunk(x, y, z);
                ChunkMesh* chunkMesh = world.getChunkMesh(x, y, z);
                if (chunk == nullptr || chunkMesh == nullptr) continue;
                if (!frustrum->isVisible(chunk)) continue;
                renderer.draw(camera, *chunk, *chunkMesh);
            }
        }
    }
    renderer.drawVoxel(camera);
    renderer.drawCursor(camera);
}

void Game::update(float deltaTime) {
    player.update(deltaTime);
}

void Game::quit() {
    stoneTexture.destroy();
    brickTexture.destroy();
    running = false;
    delete chunkLoadingThreadPool;
}

Player& Game::getPlayer() {
    return this->player;
}

World& Game::getWorld() {
    return world;
}

Camera& Game::getCamera() {
    return camera;
}

bool Game::isRunning() {
    return this->running;
}