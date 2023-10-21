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

int k = 0;

void Game::init() {
    running = true;
    world = World(WorldType::DEFAULT);
    glm::vec3 playerPosition = glm::vec3(400, int(WORLD_HEIGHT * CHUNK_SIZE / 2), 400);
    player = Player(playerPosition);
    camera = Camera(GameConfiguration::WINDOW_WIDTH, GameConfiguration::WINDOW_HEIGHT, playerPosition);
    frustrum = new FrustrumCulling(&camera);
    chunkNeedToBeRemoved = false;
    initListeners();
    //chunkLoadingThreadPool = new ThreadPool(std::thread::hardware_concurrency());
    chunkLoadingThreads.emplace_back([this]() { 
        this->loadChunks();
    });
    /*
    chunkLoadingThreads.emplace_back([this]() { 
        this->unloadChunks();
    });
    */
}

void Game::initListeners() {
    player.addEventListener(new PlayerListener());
}

void Game::unloadChunks() {
    std::cout << "Lancement de la tache de suppression !" << std::endl;
    for (ChunkCoordinates chunkCoords : chunksToRemove) {
        Chunk* chunk = world.getChunk(chunkCoords.x, chunkCoords.y, chunkCoords.z);

        if (chunk != nullptr) {
            chunk->unload();
            world.getChunks().erase(chunkCoords);
            delete chunk;
            // std::cout << "Suppression d'un chunk !" << std::endl;
        }
    }
    chunksToRemove.clear();
}

void Game::loadChunks() {

    ChunkManager chunkManager;
    std::vector<glm::ivec3> travelledPos;

    while (true) {
        
        std::vector<std::pair<glm::ivec3, float>> chunksWithDistance;

        int startX = std::max(0, int(player.getPosition().x / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));
        int startZ = std::max(0, int(player.getPosition().z / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));

        int endX = player.getPosition().x / CHUNK_SIZE + CHUNK_RENDER_DISTANCE;
        int endZ = player.getPosition().z / CHUNK_SIZE + CHUNK_RENDER_DISTANCE;

        for (int x = startX; x < endX; x++) {
            for (int y = 0; y < 16; y++) {
                for (int z = startZ; z < endZ; z++) {
                    glm::ivec3 chunkPos(x, y, z);
                    float distance = glm::length(player.getPosition() - (glm::vec3(chunkPos) * static_cast<float>(CHUNK_SIZE)));
                    chunksWithDistance.push_back(std::make_pair(chunkPos, distance));
                }
            }
        }

        std::sort(chunksWithDistance.begin(), chunksWithDistance.end(),
            [](const std::pair<glm::ivec3, float>& a, const std::pair<glm::ivec3, float>& b) {
                return a.second < b.second;
        });

        for (const auto& pair : chunksWithDistance) {
            const glm::ivec3& chunkPos = pair.first;
            Chunk* chunk = world.getChunk(chunkPos.x, chunkPos.y, chunkPos.z);
            if (chunk != nullptr && chunk->getMesh() != nullptr) continue;
            std::unique_lock<std::mutex> lock(chunkRemoveMutex);
            if (chunk != nullptr) {
                ChunkMesh* chunkMesh = chunk->getMesh();
                if (chunkMesh == nullptr) {
                    ChunkMeshData chunkMeshData = chunkManager.loadChunkMeshData(chunk);
                    ChunkMesh* chunkMesh = new ChunkMesh(chunkMeshData);
                    WaterMesh* waterMesh = new WaterMesh(chunk->getX(), chunk->getY(), chunk->getZ(), chunk->getBlocks());
                    chunk->setMesh(chunkMesh);
                    if (!waterMesh->getVertices().empty()) {
                        chunk->setWaterMesh(waterMesh);
                    } else {
                        waterMesh->unload();
                        delete waterMesh;
                    }
                }
            } else {
                chunk = chunkManager.loadChunk(chunkPos.x, chunkPos.y, chunkPos.z);
                if (!chunk->isEmpty() && chunk->getBlocks() != nullptr) {
                    world.addChunk(chunk);
                    ChunkMeshData chunkMeshData = chunkManager.loadChunkMeshData(chunk);
                    ChunkMesh* chunkMesh = new ChunkMesh(chunkMeshData);
                    WaterMesh* waterMesh = new WaterMesh(chunk->getX(), chunk->getY(), chunk->getZ(), chunk->getBlocks());
                    chunk->setMesh(chunkMesh);
                    if (!waterMesh->getVertices().empty()) {
                        chunk->setWaterMesh(waterMesh);
                    } else {
                        waterMesh->unload();
                        delete waterMesh;
                    }
                } else {
                    chunk->unload();
                    delete chunk;
                }
            }
        }

        chunksWithDistance.clear();
    }
}

void Game::render(Renderer& renderer) {

    for (auto it = world.getChunks().begin(); it != world.getChunks().end(); ++it) {
        Chunk* chunk = it->second;
        if (chunk == nullptr) continue;
        if (chunk->outOfView()) {
            ChunkCoordinates chunkCoords = ChunkCoordinates{chunk->getX(), chunk->getY(), chunk->getZ()};
            chunksToRemove.push_back(chunkCoords);
            conditionVariable.notify_one();
            // it = world.getChunks().erase(it);
        } else {
            ChunkMesh* chunkMesh = chunk->getMesh();
            if (chunkMesh != nullptr) {
                if (!chunkMesh->isMeshInitiated()) chunkMesh->initMesh();
                if (frustrum->isVisible(chunk)) {
                    renderer.draw(camera, *chunk, *chunkMesh);
                }
            }
        }
    }

    renderer.drawVoxel(camera);
    renderer.drawCursor(camera);
    renderer.drawHand();
    renderer.drawHotbar(player.getHotbar());
}

void Game::update(float deltaTime) {
    player.update(deltaTime);
    k++;
    if (k >= 200) {
        //this->unloadChunks();
        k = 0;
    }
}

void Game::quit() {
    stoneTexture.destroy();
    brickTexture.destroy();
    running = false;
    delete frustrum;
    // delete chunkLoadingThreadPool;
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