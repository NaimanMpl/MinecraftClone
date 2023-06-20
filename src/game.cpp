#include <glm/gtc/matrix_transform.hpp>
#include "game.h"
#include "texture.h"

Texture stoneTexture("../assets/textures/stone.png");    
Texture brickTexture("../assets/textures/brick.png");

Game::Game() {
    
}

void Game::init() {
    world = World(WorldType::FLAT);
    camera = Camera(800, 600, glm::vec3(0.3f, 0.2f, 2.0f));
    initTexture();
    initWorld();
}

void Game::initTexture() {
    stoneTexture.load();
    brickTexture.load();    
}

void Game::initWorld() {
    glm::vec3 blockPos = glm::vec3(0.0f, -0.5f, -2.0f);
    glm::vec3 blockPos1 = glm::vec3(0.3f, -0.8f, -2.0f);

    Block stoneBlock(stoneTexture.ID, blockPos);
    Block stoneBlock2(brickTexture.ID, blockPos1);

    world.addBlock(stoneBlock);
    world.addBlock(stoneBlock2);

}

World Game::getWorld() {
    return world;
}

Camera Game::getCamera() {
    return camera;
}

void Game::quit() {
    stoneTexture.destroy();
    brickTexture.destroy();
}