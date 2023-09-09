#include "entity/player.h"
#include "world/world.h"
#include "game.h"
#include "utils.h"

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
    maxSpeed = 30.0f;
    breakingBlock = false;
    moving = false;
    hitbox = Hitbox(Point3D{0.0f, 0.0f, 0.0f}, Point3D{0.2f, 1.0f, 0.2f});
}

Ray& Player::getRay() {
    return this->ray;
}

bool Player::collide(glm::vec3 position) {

    World& world = Game::getInstance().getWorld();
    Chunk* chunk = world.getChunkAt(position - 0.25f);
    Block* block = world.getBlockAt(position - 0.25f);

    if (block == nullptr) return false;

    return block->getMaterial().isSolid();
}

bool Player::collideWithWorld(glm::vec3 newPosition) {
    World& world = Game::getInstance().getWorld();

    std::cout << "--------- DEBUT ----------" << std::endl;

    for (float x = newPosition.x - 0.5f / 2; x < newPosition.x + hitbox.getWidth() / 2; x += 0.05f) {
        for (float y = newPosition.y - 1.5f; y < newPosition.y + 0.99f; y += 0.05f) {
            for (float z = newPosition.z - 0.5f / 2; z < newPosition.z + hitbox.getDepth() / 2; z += 0.05f) {
                Block* block = world.getBlockAt(x, y, z);
                if (block == nullptr) {
                    std::cout << "AIR" << std::endl;
                    continue;
                } else {
                    std::cout << block->getMaterial().getName() << std::endl;
                    Chunk* chunk = world.getChunkAt(x, y, z);
                    std::cout << "Position : x = " << chunk->getX() * CHUNK_SIZE + block->getX() << " y = " << chunk->getY() * CHUNK_SIZE + block->getY() << " z = " << chunk->getZ() * CHUNK_SIZE + block->getZ() << std::endl;
                    Utils::display(newPosition); 
                }
                if (block->getMaterial().isSolid()) return true;
            }
        }
    }
    std::cout << "--------- FIN ----------" << std::endl;

    return false;
}


void Player::update(float deltaTime) {
    Camera& camera = Game::getInstance().getCamera();
    World& world = Game::getInstance().getWorld();

    setBreakingBlock(false);

    velocity += acceleration * speed * deltaTime;
    acceleration = glm::vec3(0.0f);

    if (gameMode == GameMode::SURVIVAL) {
        Block* block = world.getBlockAt(position.x, position.y - hitbox.getHeight(), position.z);
        if (block == nullptr) {
            velocity += gravity * deltaTime;
        } else {
            inAir = false;
        }
    }

    if (glm::length(velocity) > maxSpeed) {
        velocity = glm::normalize(velocity) * maxSpeed;
    }

    glm::vec3 newPosition = position + velocity * deltaTime;

    // bool collision = collideWithWorld(newPosition - glm::vec3(0.0f, 4.0f, 0.0f));

    position = newPosition;

    // Utils::display(position);

    velocity.x *= 0.95;
    velocity.z *= 0.95;
    
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

    moving = false;
    Camera& camera = Game::getInstance().getCamera();

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
                velocity.y = 15.0f;
                inAir = true;
            }
        }
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