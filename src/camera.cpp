#include "camera.h"
#include "game_configuration.h"

Camera::Camera() {

}

Camera::Camera(int width, int height, glm::vec3 position) {
    orientation = glm::vec3(0.0f, 4.0f, 1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    speed = 10.0f;
    sensitivity = 100.0f;
    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
    Camera::width = width;
    Camera::height = height;
    Camera::position = position;
}

void Camera::matrix(Block block, float fovDeg, float nearPlane, float farPlane, Shader shader, const char* uniform) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(position + block.getPosition(), position + block.getPosition() + orientation, up);
    projection = glm::perspective(glm::radians(fovDeg), (float) (width / height), nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::inputs(GLFWwindow* window, float deltaTime) {

    // Keyboard Events
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position += speed * orientation * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        position += speed * -glm::normalize(glm::cross(orientation, up)) * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position += speed * -orientation * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position += speed * glm::normalize(glm::cross(orientation, up)) * deltaTime;
    }

    // Mouse events
    int centerX = GameConfiguration::WINDOW_WIDTH / 2;
    int centerY = GameConfiguration::WINDOW_HEIGHT / 2;
    int MOUSE_MARGIN = 10;
    float MOUSE_SPEED = 5.0f;

    double mouseX, mouseY;

    glfwGetCursorPos(window, &mouseX, &mouseY);

    if (mouseX > centerX + MOUSE_MARGIN) {
    }
    if (mouseX < centerX - MOUSE_MARGIN) {
    }
    
    if (mouseY > centerY + MOUSE_MARGIN) {
        orientation += glm::vec3(0.0f, -MOUSE_SPEED, 0.0f) * deltaTime;
    }
    if (mouseY < centerY - MOUSE_MARGIN) {
        orientation += glm::vec3(0.0f, MOUSE_SPEED, 0.0f) * deltaTime;
    }

    glfwSetCursorPos(window, centerX, centerY);

}