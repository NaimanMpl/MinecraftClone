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
    glm::vec3 playerPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    camera = Camera(GameConfiguration::WINDOW_WIDTH, GameConfiguration::WINDOW_HEIGHT, playerPosition);
    initTexture();
    initWorld();
}

void Game::initTexture() {
}

void Game::initWorld() {
    if (world.getType() == WorldType::FLAT) {
        std::vector<Block> blocks;
        for (unsigned int x = 0; x < GameConfiguration::CHUNK_SIZE; x++) {
            for (unsigned int y = 0; y < GameConfiguration::CHUNK_SIZE; y++) {
                for (unsigned int z = 0; z < GameConfiguration::CHUNK_SIZE; z++) {
                    Block block(Material::BRICK, x, y, z);
                    blocks.push_back(block);
                }
            }
        }
        Chunk chunk(blocks, glm::vec3(0.0f, 0.0f, 0.0f));
        ChunkMesh chunkMesh(chunk);
        world.addChunk(chunk, chunkMesh);
    }
}

void Game::render(Renderer& renderer) {
    for (int i = 0; i < world.getChunks().size(); i++) {
        Chunk chunk = world.getChunks().at(i);
        ChunkMesh chunkMesh = world.getChunksMeshs().at(i);
        renderer.draw(camera, chunk, chunkMesh);
    }
}

void Game::update() {

}

void Game::quit() {
    stoneTexture.destroy();
    brickTexture.destroy();
}

World Game::getWorld() {
    return world;
}

Camera& Game::getCamera() {
    return camera;
}