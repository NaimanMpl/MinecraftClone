#include "entity/entity.h"

Entity::Entity() {}

Entity::Entity(glm::vec3& position) {
    this->position = position;
    this->velocity = glm::vec3(0.0f);
    this->acceleration = glm::vec3(0.0f);
    this->gravity = glm::vec3(0.0f, -10.0f, 0.0f);
    this->movingLeft = false;
    this->movingRight = false;
    this->movingForward = false;
    this->movingBackward = false;
    this->inAir = true;
    this->yaw = 0.0f;
    this->pitch = -90.0f;
}

glm::vec3& Entity::getPosition() {
    return this->position;
}

glm::vec3& Entity::getVelocity() {
    return this->velocity;
}

glm::vec3& Entity::getAcceleration() {
    return this->acceleration;
}

Hitbox& Entity::getHitbox() {
    return this->hitbox;
}

bool Entity::isInAir() {
    return this->inAir;
}

float Entity::getSpeed() {
    return this->speed;
}

float Entity::getYaw() {
    return this->yaw;
}

float Entity::getPitch() {
    return this->pitch;
}

void Entity::addEventListener(EventListener* listener) {
    listeners.push_back(listener);
}