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

const double Game::TICK_RATE = 20.0;
const double Game::TICK_INTERVAL = 1.0 / Game::TICK_RATE;

Game::Game() {

}

int k = 0;

void Game::init() {
    this->running = true;
    this->world = World(WorldType::DEFAULT);
    glm::vec3 playerPosition = glm::vec3(0, 0, 0);
    this->player = Player(playerPosition);
    this->camera = Camera(GameConfiguration::WINDOW_WIDTH, GameConfiguration::WINDOW_HEIGHT, playerPosition);
    this->frustrum = new FrustrumCulling(&camera);
    this->chunkNeedToBeRemoved = false;
    this->elapsedTime = 0.0f;
    this->lastTickTime = 0.0;
    this->currentTickTime = 0.0;
    this->updateTimer = 0.0f;
    initListeners();
    chunkLoadingThreadPool = new ThreadPool(std::thread::hardware_concurrency());
    chunkLoadingThreads.emplace_back([this]() { 
        this->loadChunks();
    });

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
            std::unique_lock<std::mutex> lock(this->chunkLoadingMutex);
            Chunk* chunk = world.getChunk(chunkPos.x, chunkPos.y, chunkPos.z);
            if (chunk != nullptr && chunk->getMesh() != nullptr) continue;
            /*
            std::unique_lock<std::mutex> lock(chunkRemoveMutex);
            if (std::find(chunksToRemove.begin(), chunksToRemove.end(), ChunkCoordinates{chunkPos.x, chunkPos.y, chunkPos.z}) != chunksToRemove.end()) continue;
            */
           if (chunk != nullptr) {
                ChunkMesh* chunkMesh = chunk->getMesh();
                if (chunkMesh == nullptr && !chunk->isMeshLoaded()) {
                    ChunkMeshData chunkMeshData = chunkManager.loadChunkMeshData(chunk);
                    ChunkMesh* chunkMesh = new ChunkMesh(chunkMeshData);
                    WaterMesh* waterMesh = new WaterMesh(chunk->getX(), chunk->getY(), chunk->getZ(), chunk->getBlocks());
                    DoubleQuadMesh* doubleQuadMesh = new DoubleQuadMesh(chunk->getBlocks());
                    
                    chunk->loadMeshes(chunkMesh, waterMesh, doubleQuadMesh);

                    // std::cout << "La ChunkMesh (" << chunkPos.x << ", " << chunkPos.y << ", " << chunkPos.z << ") a été généré !" << std::endl; 
                }
            } else {
                ChunkManager chunkManager;

                Chunk* chunk = chunkManager.loadChunk(chunkPos.x, chunkPos.y, chunkPos.z);
                if (!chunk->isEmpty() && chunk->getBlocks() != nullptr) {
                    world.addChunk(chunk);
                    ChunkMeshData chunkMeshData = chunkManager.loadChunkMeshData(chunk);
                    ChunkMesh* chunkMesh = new ChunkMesh(chunkMeshData);
                    WaterMesh* waterMesh = new WaterMesh(chunk->getX(), chunk->getY(), chunk->getZ(), chunk->getBlocks());
                    DoubleQuadMesh* doubleQuadMesh = new DoubleQuadMesh(chunk->getBlocks());
                    
                    chunk->loadMeshes(chunkMesh, waterMesh, doubleQuadMesh);

                    // std::cout << "Le chunk (" << chunkPos.x << ", " << chunkPos.y << ", " << chunkPos.z << ") a été généré !" << std::endl; 
                    
                } else {
                    chunk->unload();
                    delete chunk;
                }

            }
            lock.unlock();
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
            // chunksToRemove.push_back(chunkCoords);
            conditionVariable.notify_one();
            // it = world.getChunks().erase(it);
        } else {
            ChunkMesh* chunkMesh = chunk->getMesh();
            if (chunkMesh != nullptr) {
                if (!chunkMesh->isMeshInitiated()) chunkMesh->init();
                if (frustrum->isVisible(chunk)) {
                    renderer.draw(camera, *chunk, *chunkMesh);
                }
            }
        }
    }
    for (auto it = world.getChunks().begin(); it != world.getChunks().end(); ++it) {
        Chunk* chunk = it->second;
        if (chunk == nullptr) continue;
        if (frustrum->isVisible(chunk) && !chunk->outOfView()) {
            renderer.drawWater(camera, *chunk);
        }
    }

    renderer.drawVoxel(camera);
    renderer.drawCursor(camera);
    renderer.drawHand();
    renderer.drawHotbar(player.getHotbar());
}

void Game::updateGameLogic() {
    elapsedTime += 0.05f;
}

void Game::updateTick() {
    currentTickTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count() / 1000.0;
    if (currentTickTime - lastTickTime > TICK_INTERVAL) {
        this->updateGameLogic();
        lastTickTime = currentTickTime;
    }
}

void Game::update() {
    player.update();
    this->updateTick();
    k++;
    if (k >= 200) {
        // this->unloadChunks();
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

float Game::getElapsedTime() {
    return this->elapsedTime;
}

float Game::getUpdateTimer() {
    return this->updateTimer;
}

void Game::setUpdateTimer(float time) {
    this->updateTimer = time;
}
