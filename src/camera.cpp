#include "camera.h"
#include "game_configuration.h"
#include "chunkmanager.h"
#include "player.h"
#include "game.h"

Camera::Camera() {

}

Camera::Camera(int width, int height, glm::vec3 position) {
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::vec3(1.0f, 0.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    orientation = glm::vec3(0.0f, 4.0f, 1.0f);
    speed = 30.0f;
    sensitivity = 10.0f;
    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
    yaw = 0.0f;
    pitch = -90.0f;
    fov = 45.0f;
    nearPlane = 0.1f;
    farPlane = 500.0f;
    mouseX = 0.0f;
    mouseY = 0.0f;
    mouseOffsetX = 0.0f;
    mouseOffsetY = 0.0f;
    lastMouseX = 0.0f;
    lastMouseY = 0.0f;
    firstMouse = true;
    Camera::width = width;
    Camera::height = height;
    Camera::position = position;
}

void Camera::matrix(Block block, Shader& shader, const char* uniform) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));

    // model = glm::translate(model, block.getPosition());
    view = glm::lookAt(position, position + front, up);
    projection = glm::perspective(glm::radians(fov), (float) width / height, nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view * model));
}

void Camera::matrix(Chunk chunk, Shader& shader, const char* uniform) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));

    model = glm::translate(model, glm::vec3(chunk.getPosition() * CHUNK_SIZE));
    view = glm::lookAt(position, position + front, up);
    projection = glm::perspective(glm::radians(fov), (float) width / height, nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view * model));
}

glm::vec3 Camera::getPosition() {
    return this->position;
}

glm::vec3 Camera::getFront() {
    return this->front;
}

void Camera::inputs(GLFWwindow* window, float deltaTime) {

    // Keyboard Events
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += front * speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position -= right * speed * deltaTime;   
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position -= front * speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += right * speed * deltaTime;
    }

    // Mouse events

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

    pitch -= mouseOffsetY * sensitivity * deltaTime;
    yaw += mouseOffsetX * sensitivity * deltaTime;

    if (pitch >= 89.0f) {
        pitch = 89.0f; 
    } else if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    if (yaw >= 360.0f || yaw < -360.0f) {
       yaw = 0.0f; 
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        ChunkManager chunkManager;
        Player& player = Game::getInstance().getPlayer();
        Block* block = player.getRay().getBlock();
        Chunk* chunk = player.getRay().getChunk();
        if (block == nullptr || chunk == nullptr) return;
        chunkManager.removeBlock(chunk, block);
        std::cout << block->getMaterial().getName() << "Removed" << std::endl;
    }
}