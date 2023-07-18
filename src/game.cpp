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
    glm::vec3 playerPosition = glm::vec3(0.0f, 2.0f, 0.0f);
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
                glm::vec3 blockPosition = glm::vec3(i, 0.0f, j);
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