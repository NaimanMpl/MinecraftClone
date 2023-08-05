#include <glm/gtc/matrix_transform.hpp>
#include "game.h"
#include "texture.h"
#include "game_configuration.h"

Texture stoneTexture("../assets/textures/stone.png");    
Texture brickTexture("../assets/textures/brick.png");
Texture grassTexture("../assets/textures/sand.png");

Game::Game() {
    
}

void Game::init() {
    world = World(WorldType::FLAT, 50, 50);
    glm::vec3 playerPosition = glm::vec3(int(WORLD_WIDTH * CHUNK_SIZE / 2), int(WORLD_HEIGHT * CHUNK_SIZE / 2), int(WORLD_DEPTH * CHUNK_SIZE / 2));
    camera = Camera(GameConfiguration::WINDOW_WIDTH, GameConfiguration::WINDOW_HEIGHT, playerPosition);
    initTexture();
    initWorld();
}

void Game::initTexture() {
}

void Game::initWorld() {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int y = 0; y < WORLD_HEIGHT; y++) {
            for (int z = 0; z < WORLD_DEPTH; z++) {
                Chunk* chunk = new Chunk(x, y, z);
                world.addChunk(chunk);
            }
        }
    }
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int y = 0; y < WORLD_HEIGHT; y++) {
            for (int z = 0; z < WORLD_DEPTH; z++) {
                Chunk* chunk = world.getChunk(x, y, z);
                if (chunk == nullptr) continue;
                ChunkMesh* chunkMesh = new ChunkMesh(*chunk);
                world.addChunkMesh(chunkMesh);
            }
        }
    }
    std::cout << "Le monde a été correctement initié !" << std::endl;
}

void Game::render(Renderer& renderer) {
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int y = 0; y < WORLD_HEIGHT; y++) {
            for (int z = 0; z < WORLD_DEPTH; z++) {
                Chunk* chunk = world.getChunk(x, y, z);
                ChunkMesh* chunkMesh = world.getChunkMesh(x, y, z);
                if (chunk == nullptr) continue;
                renderer.draw(camera, *chunk, *chunkMesh);
            }
        }
    }
    renderer.drawCursor(camera);
    renderer.drawVoxel(camera);
}

void Game::update() {
    player.update();
}

void Game::quit() {
    stoneTexture.destroy();
    brickTexture.destroy();
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