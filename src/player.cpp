#include "player.h"

Player::Player() {

}

Ray& Player::getRay() {
    return this->ray;
}

void Player::update() {
    ray.update();
}