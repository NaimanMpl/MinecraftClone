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
    world = World(WorldType::FLAT, 20, 20);
    glm::vec3 playerPosition = glm::vec3((int) (GameConfiguration::CHUNK_SIZE / 2), GameConfiguration::CHUNK_SIZE, 1.5f * GameConfiguration::CHUNK_SIZE);
    camera = Camera(GameConfiguration::WINDOW_WIDTH, GameConfiguration::WINDOW_HEIGHT, playerPosition);
    initTexture();
    initWorld();
}

void Game::initTexture() {
    stoneTexture.load();
    brickTexture.load();    
    grassTexture.load();
}

void Game::initWorld() {
    if (world.getType() == WorldType::FLAT) {
        for (int i = 0; i < world.getWidth(); i++) {
            for (int j = 0; j < world.getHeight(); j++) {
                glm::vec3 blockPosition = glm::vec3(i * GameConfiguration::GAME_SCALE, j * GameConfiguration::GAME_SCALE, -2.0f);
                Block block(stoneTexture.ID, blockPosition);
                world.addBlock(block);
            }
        }
    }
}

void Game::render(Renderer& renderer) {
    for (const Block& block : world.getBlocks()) {
        renderer.draw(camera, block);
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