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

bool once = true;

Game::Game() {
    
}

void Game::init() {
    running = true;
    world = World(WorldType::DEFAULT);
    glm::vec3 playerPosition = glm::vec3(800, int(WORLD_HEIGHT * CHUNK_SIZE / 2), 800);
    player = Player(playerPosition);
    camera = Camera(GameConfiguration::WINDOW_WIDTH, GameConfiguration::WINDOW_HEIGHT, playerPosition);
    frustrum = new FrustrumCulling(&camera);
    unloadedChunks = new std::priority_queue<std::pair<ChunkMeshData, Chunk*>, std::vector<std::pair<ChunkMeshData, Chunk*>>, ChunkMeshDataComparator>();
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

    for (unsigned int x = 0; x < 1; x++) {
        for (unsigned int y = 0; y < 1; y++) {
            for (unsigned int z = 0; z < 1; z++) {
                Chunk* chunk = new Chunk(x, y, z);
                for (int chunkX = 0; chunkX < 1; chunkX++) {
                    for (int chunkY = 0; chunkY < 1; chunkY++) {
                        for (int chunkZ = 0; chunkZ < 1; chunkZ++) {
                            Block* block = new Block(Material::STONE, 10, 10, 10);
                            chunk->addBlock(block);
                        }
                    }
                }
                world.addChunk(chunk);
            }
        }
    }
    for (unsigned int x = 0; x < 1; x++) {
        for (unsigned int y = 0; y < 1; y++) {
            for (unsigned int z = 0; z < 1; z++) {
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

void remove(std::vector<ChunkCoordinates>* chunks, ChunkCoordinates coords) {
    auto it = chunks->begin();
    while (it != chunks->end()) {
        if (*it == coords) {
            it = chunks->erase(it);
        } else {
            ++it;
        }
    }
}

void Game::loadChunks() {

    ChunkManager chunkManager;

    while (true) {
        
        std::vector<std::pair<glm::ivec3, float>> chunksWithDistance;

        int startX = std::max(0, int(player.getPosition().x / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));
        int startY = std::max(0, int(player.getPosition().y / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));
        int startZ = std::max(0, int(player.getPosition().z / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));

        int endX = player.getPosition().x / CHUNK_SIZE + CHUNK_RENDER_DISTANCE;
        int endY = player.getPosition().y / CHUNK_SIZE + CHUNK_RENDER_DISTANCE;
        int endZ = player.getPosition().z / CHUNK_SIZE + CHUNK_RENDER_DISTANCE;

        for (int x = startX; x < endX; x++) {
            for (int y = startY; y < endY; y++) {
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
            if (exists(viewedChunks, chunkPos)) continue;
            viewedChunks.push_back(chunkPos);
            Chunk* chunk = world.getChunk(chunkPos.x, chunkPos.y, chunkPos.z);
            if (chunk == nullptr) {
                chunk = chunkManager.loadChunk(chunkPos.x, chunkPos.y, chunkPos.z);
            }
            ChunkMeshData chunkMeshData = chunkManager.loadChunkMeshData(chunk);
            ChunkMesh* chunkMesh = new ChunkMesh(*chunk, chunkMeshData);
            world.addChunkMesh(chunkMesh);
        }

        chunksWithDistance.clear();
    }
}

bool Game::outOfView(Chunk* chunk, int startX, int startY, int startZ, int endX, int endY, int endZ) {
    return chunk->getX() < startX || chunk->getY() < startY || chunk->getZ() < startZ || chunk->getX() > endX || chunk->getY() > endY || chunk->getZ() > endZ;
}


void Game::render(Renderer& renderer) {

    int startX = std::max(0, int(player.getPosition().x / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));
    int startY = std::max(0, int(player.getPosition().y / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));
    int startZ = std::max(0, int(player.getPosition().z / CHUNK_SIZE - CHUNK_RENDER_DISTANCE));

    int endX = player.getPosition().x / CHUNK_SIZE + CHUNK_RENDER_DISTANCE;
    int endY = player.getPosition().y / CHUNK_SIZE + CHUNK_RENDER_DISTANCE;
    int endZ = player.getPosition().z / CHUNK_SIZE + CHUNK_RENDER_DISTANCE;

    for (auto it = world.getChunks().begin(); it != world.getChunks().end();) {
        Chunk* chunk = it->second;
        if (chunk != nullptr) {
            if (this->outOfView(chunk, startX, startY, startZ, endX, endY, endZ)) {
                ++it;
            } else {
                ChunkMesh* chunkMesh = world.getChunkMesh(chunk->getX(), chunk->getY(), chunk->getZ());
                if (chunkMesh != nullptr) {
                    if (!chunkMesh->isMeshInitiated()) chunkMesh->initMesh();
                    if (frustrum->isVisible(chunk)) {
                        renderer.draw(camera, *chunk, *chunkMesh);
                    }
                }
                ++it;
            }
        }
    }

    renderer.drawVoxel(camera);
    renderer.drawCursor(camera);
    renderer.drawHand();
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