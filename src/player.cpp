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