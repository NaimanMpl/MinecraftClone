#include "entity/player.h"
#include "world/world.h"
#include "game.h"

Player::Player() {}

Player::Player(glm::vec3 position) : Entity(position) {
    this->speed = 30.0f;
    gameMode = GameMode::CREATIVE;
    mouseX = 0.0f;
    mouseY = 0.0f;
    mouseOffsetX = 0.0f;
    mouseOffsetY = 0.0f;
    lastMouseX = 0.0f;
    lastMouseY = 0.0f;
    firstMouse = true;
    maxSpeed = 50.0f;
    breakingBlock = false;
    hitbox = Hitbox(Point3D{0.0f, 0.0f, 0.0f}, Point3D{0.5f, 1.5f, -0.5f});
}

Ray& Player::getRay() {
    return this->ray;
}

bool Player::collide(glm::vec3 position) {

    World& world = Game::getInstance().getWorld();
    Block* block = world.getBlockAt(position);

    if (block == nullptr) return false;

    return block->getMaterial().isSolid();
}

bool Player::collideWithWorld(glm::vec3 newPosition) {

    glm::vec3 leftBottomCornerPosition = newPosition;
    glm::vec3 rightBottomCornerPosition = glm::vec3(newPosition.x + hitbox.getWidth(), newPosition.y, newPosition.z);
    glm::vec3 rightUpCornerPosition = glm::vec3(newPosition.x + hitbox.getWidth(), newPosition.y + hitbox.getWidth(), newPosition.z);
    glm::vec3 leftUpCornerPosition = glm::vec3(newPosition.x, newPosition.y + hitbox.getHeight(), newPosition.z);
    glm::vec3 c4 = glm::vec3(newPosition.x + hitbox.getWidth(), newPosition.y, newPosition.z + hitbox.getDepth());
    glm::vec3 c5 = glm::vec3(newPosition.x + hitbox.getWidth(), newPosition.y + hitbox.getHeight(), newPosition.z + hitbox.getDepth());
    glm::vec3 c6 = glm::vec3(newPosition.x, newPosition.y, newPosition.z + hitbox.getDepth());
    glm::vec3 c7 = glm::vec3(newPosition.x, newPosition.y + hitbox.getHeight(), newPosition.z + hitbox.getDepth());
    
    return (
        collide(leftBottomCornerPosition) || 
        collide(rightBottomCornerPosition) || 
        collide(rightUpCornerPosition) || 
        collide(leftUpCornerPosition) || 
        collide(c4) || 
        collide(c5) || 
        collide(c6) || 
        collide(c7)
    );
}

void Player::update(float deltaTime) {
    Camera& camera = Game::getInstance().getCamera();
    World& world = Game::getInstance().getWorld();

    setBreakingBlock(false);

    velocity += acceleration * speed * deltaTime;

    if (gameMode == GameMode::SURVIVAL) {
        Block* block = world.getBlockAt(position.x, position.y - hitbox.getHeight(), position.z);
        if (block == nullptr) {
            velocity += gravity * deltaTime;
        } else {
            if (!inAir) {
                if (this->isImmobile()) {
                    velocity = glm::vec3(0.0f);
                } else {
                    velocity.y = 0.0f;
                }
            } else {
                inAir = false;
            }
        }
    } else {
        if (this->isImmobile()) velocity = glm::vec3(0.0f);
    }


    /*
    if (collideWithWorld(position + velocity * deltaTime)) {
        velocity = glm::vec3(0.0f);
    }
    */

    if (glm::length(velocity) > maxSpeed) {
        velocity = glm::normalize(velocity) * maxSpeed;
    }

    position += velocity * deltaTime;
    
    camera.update(this);
    ray.update();
}

bool Player::isImmobile() {
    return !movingLeft && !movingRight && !movingForward && !movingBackward;
}

bool Player::isSneaking() {
    return sneaking;
}

bool Player::isBreakingBlock() {
    return this->breakingBlock;
}

void Player::setBreakingBlock(bool breakingBlock) {
    this->breakingBlock = breakingBlock;
}

void Player::breakBlock(Chunk* chunk, Block* block) {
    setBreakingBlock(true);
    for (EventListener* listener : listeners) {
        listener->onBlockBreak(new BlockBreakEvent(this, chunk, block));
    }
}

void Player::handleInputs(GLFWwindow* window, float deltaTime) {

    acceleration = glm::vec3(0.0f);
    Camera& camera = Game::getInstance().getCamera();

    glm::vec3 front = glm::vec3(1.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        acceleration += front;
        movingForward = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        acceleration -= right;   
        movingLeft = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        acceleration -= front;
        movingBackward = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        acceleration += right;
        movingRight = true;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        if (gameMode == GameMode::CREATIVE) {
            acceleration -= up;
        }
        sneaking = true;
    }
    
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (gameMode == GameMode::CREATIVE) {
            position.y += 10.0f * deltaTime;
        } else if (gameMode == GameMode::SURVIVAL) {
            if (!inAir) {
                velocity.y = 15.0f;
                inAir = true;
            }
        }
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE) {
        movingForward = false;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE) {
        movingLeft = false;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE) {
        movingBackward = false;
    }
    
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE) {
        movingRight = false;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE && gameMode == GameMode::CREATIVE) {
        velocity.y = 0.0f;
        sneaking = false;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (ray.getChunk() != nullptr && ray.getBlock() != nullptr && !breakingBlock) {
            this->breakBlock(ray.getChunk(), ray.getBlock());
        }
    }

    double mouseX, mouseY;

    glfwGetCursorPos(window, &mouseX, &mouseY);

    if (firstMouse) {
        lastMouseX = mouseX;
        lastMouseY = mouseY;
        firstMouse = false;
    }

    mouseOffsetX = mouseX - lastMouseX;
    mouseOffsetY = mouseY - lastMouseY;

    lastMouseX = mouseX;
    lastMouseY = mouseY;

    pitch -= mouseOffsetY * camera.getSensitivity() * deltaTime;
    yaw += mouseOffsetX * camera.getSensitivity() * deltaTime;

    if (pitch >= 89.0f) {
        pitch = 89.0f; 
    } else if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    if (yaw >= 360.0f || yaw < -360.0f) {
       yaw = 0.0f; 
    }
}