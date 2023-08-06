#include "player.h"

Player::Player() {
    this->canBreakBlock = true;
}

Ray& Player::getRay() {
    return this->ray;
}

void Player::update() {
    ray.update();
}

void Player::breakBlock(Chunk* chunk, Block* block) {
    for (auto& listener : listeners) {
        listener.onBreakBlock(new BlockBreakEvent(this, chunk, block));
    }
}

void Player::addEventListener(PlayerEventListener listener) {
    listeners.push_back(listener);
}