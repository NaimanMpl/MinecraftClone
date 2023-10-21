#include "entity/player.h"
#include "world/world.h"
#include "game.h"
#include "utils.h"

Player::Player() {}

Player::Player(glm::vec3 position) : Entity(position) {
    gameMode = GameMode::CREATIVE;
    mouseX = 0.0f;
    mouseY = 0.0f;
    mouseOffsetX = 0.0f;
    mouseOffsetY = 0.0f;
    lastMouseX = 0.0f;
    lastMouseY = 0.0f;
    firstMouse = true;
    baseSpeed = 60.0f;
    this->speed = baseSpeed;
    maxSpeed = baseSpeed;
    maxSprintSpeed = maxSpeed * 2.0f;
    fov = 70.0f;
    breakingBlock = false;
    moving = false;
    sprinting = false;
    hitbox = Hitbox(Point3D{0.0f, 0.0f, 0.0f}, Point3D{0.25f, 1.0f, 0.25f});
}

Ray& Player::getRay() {
    return this->ray;
}

Hand& Player::getHand() {
    return this->hand;
}

Hotbar& Player::getHotbar() {
    return this->hotbar;
}

void Player::handleCollisions(glm::vec3 newVelocity) {
    World& world = Game::getInstance().getWorld();

    for (int x = position.x - hitbox.getWidth(); x < position.x + hitbox.getWidth(); x++) {
        for (int y = position.y - hitbox.getHeight(); y < position.y + 0.99f; y++) {
            for (int z = position.z - hitbox.getDepth(); z < position.z + hitbox.getDepth(); z++) {
                int8_t block = world.getBlockAt(x, y, z);
                
                if (block == -1)
                    continue;
                
                if (!Utils::getMaterialFromBlock(block).isSolid())
                    continue;

                if (newVelocity.y > 0) {
                    position.y = y - hitbox.getHeight();
                    velocity.y = 0;
                } else if (newVelocity.y < 0) {
                    position.y = y + hitbox.getHeight() + 1;
                    velocity.y = 0;
                    inAir = false;
                }

                if (newVelocity.x > 0) {
                    position.x = x - hitbox.getWidth();
                } else if (newVelocity.x < 0) {
                    position.x = x + hitbox.getWidth() + 1;
                }

                if (newVelocity.z > 0) {
                    position.z = z - hitbox.getDepth();
                } else if (newVelocity.z < 0) {
                    position.z = z + hitbox.getDepth() + 1;
                }
            }
        }
    }
}


void Player::update(float deltaTime) {
    Camera& camera = Game::getInstance().getCamera();
    World& world = Game::getInstance().getWorld();

    setBreakingBlock(false);
    maxSpeed = 120.0f;
    hand.setAnimation(HandAnimation::Idle);

    if (sprinting) {
        speed = baseSpeed * 1.5f;
        camera.setFOV(camera.getFOV() + 0.6f);
        if (camera.getFOV() > fov + 12.0f) {
            camera.setFOV(fov + 12.0f);
        }
        hand.getViewBobbing()->effectSpeed = 12.0f;
    } else {
        camera.setFOV(camera.getFOV() - 0.6f);
        if (camera.getFOV() < fov) {
            camera.setFOV(fov);
        }
        hand.getViewBobbing()->effectSpeed = 8.0f;
        speed = baseSpeed;
        maxSpeed = baseSpeed;
    }

    velocity += acceleration * speed * deltaTime;
    acceleration = glm::vec3(0.0f);

    if (gameMode == GameMode::SURVIVAL)
        velocity += gravity * deltaTime;

    if (sprinting) {
        if (glm::length(velocity) > maxSprintSpeed) {
            velocity = glm::normalize(velocity) * maxSprintSpeed;
        }
    } else {
        if (glm::length(velocity) > maxSpeed) {
            velocity = glm::normalize(velocity) * maxSpeed;
        }
    }

    position.x += velocity.x * deltaTime;
    handleCollisions(glm::vec3(velocity.x, 0, 0));

    position.z += velocity.z * deltaTime;
    handleCollisions(glm::vec3(0, 0, velocity.z));

    position.y += velocity.y * deltaTime;
    handleCollisions(glm::vec3(0, velocity.y, 0));

    if (moving) hand.setAnimation(HandAnimation::Moving);

    velocity.x *= 0.95;
    velocity.z *= 0.95;

    camera.update(this);
    hand.update(camera.getRight(), deltaTime, velocity);
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

bool Player::isSprinting() {
    return this->sprinting;
}

void Player::setBreakingBlock(bool breakingBlock) {
    this->breakingBlock = breakingBlock;
}

void Player::breakBlock(Chunk* chunk, int worldX, int worldY, int worldZ, int8_t block) {
    setBreakingBlock(true);
    for (EventListener* listener : listeners) {
        BlockBreakEvent* event = new BlockBreakEvent(this, chunk, block, worldX, worldY, worldZ);
        listener->onBlockBreak(event);
        delete event;
    }
}

void Player::handleInputs(GLFWwindow* window, float deltaTime) {

    moving = false;
    sprinting = false;
    Camera& camera = Game::getInstance().getCamera();

    Game& game = Game::getInstance();

    glm::vec3 front = glm::vec3(1.0f);
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(0.0f));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        acceleration += front;
        moving = true;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        acceleration -= right;   
        moving = true;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        acceleration -= front;
        moving = true;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        acceleration += right;
        moving = true;
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
                velocity.y = 8.0f;
                inAir = true;
            }
        }
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        sprinting = true;
    }
    /*
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        game.x += 0.1f;
    }

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        game.z += 0.1f;
    }
    */

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE && gameMode == GameMode::CREATIVE) {
        velocity.y = 0.0f;
        sneaking = false;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (ray.getChunk() != nullptr && ray.getBlock() != -1 && !breakingBlock) {
            this->breakBlock(ray.getChunk(), ray.getBlockX(), ray.getBlockY(), ray.getBlockZ(), ray.getBlock());
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