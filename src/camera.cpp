#include "camera.h"
#include "game_configuration.h"
#include "game.h"

Camera::Camera() {

}

Camera::Camera(int width, int height, glm::vec3 position) {
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::vec3(1.0f, 0.0f, 0.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    orientation = glm::vec3(0.0f, 4.0f, 1.0f);
    view = glm::mat4(1.0f);
    speed = 30.0f;
    sensitivity = 10.0f;
    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
    fov = 70.0f;
    nearPlane = 0.1f;
    farPlane = 300.0f;
    Camera::width = width;
    Camera::height = height;
    Camera::position = position;
}

void Camera::matrixVoxel(Chunk chunk, Block block, Shader& shader) {
    view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));

    glm::vec3 chunkWorldPosition = chunk.getPosition() * CHUNK_SIZE;
    glm::vec3 blockWorldPosition = chunkWorldPosition + glm::vec3(block.getX(), block.getY(), block.getZ());

    model = glm::translate(model, blockWorldPosition);
    updateViewMatrix();
    projection = glm::perspective(glm::radians(fov), (float) width / height, nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(projection * view * model));
}

void Camera::matrix(Chunk chunk, Shader& shader, const char* uniform) {
    view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up = glm::normalize(glm::cross(right, front));

    model = glm::translate(model, glm::vec3(chunk.getPosition() * CHUNK_SIZE));
    updateViewMatrix();
    projection = glm::perspective(glm::radians(fov), (float) width / height, nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view * model));
}

void Camera::matrixCursor(Shader& shader, const char* uniform) {
    view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    Game& game = Game::getInstance();

    model = glm::scale(model, glm::vec3(0.15f));
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 6.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    projection = glm::perspective(glm::radians(55.0f), (float) width / height, nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view * model));
}

void Camera::updateViewMatrix() {
    view = glm::lookAt(position, position + front, up);
}


glm::vec3 Camera::getPosition() {
    return this->position;
}

glm::vec3 Camera::getFront() {
    return this->front;
}

glm::vec3 Camera::getRight() {
    return this->right;
}

glm::vec3 Camera::getUp() {
    return this->up;
}

float Camera::getFOV() {
    return this->fov;
}

void Camera::setFOV(float fov) {
    this->fov = fov;
}

float Camera::getNearPlane() {
    return this->nearPlane;
}

float Camera::getFarPlane() {
    return this->farPlane;
}

float Camera::getSensitivity() {
    return this->sensitivity;
}

void Camera::update(Player* player) {
    position = player->getPosition();
    yaw = player->getYaw();
    pitch = player->getPitch();
}

void Camera::inputs(GLFWwindow* window, float deltaTime) {

}