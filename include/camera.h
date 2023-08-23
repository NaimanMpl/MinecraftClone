#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shader.h"
#include "block.h"
#include "world/chunk.h"
#include "entity/player.h"
#include "entity/entity.h"

class Camera {
    private:
        glm::vec3 position;
        glm::vec3 orientation;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 front;
        glm::mat4 view;

        int width, height;

        float speed, sensitivity, horizontalAngle, verticalAngle, yaw, pitch, fov, nearPlane, farPlane;

        void updateViewMatrix();
    public:
        Camera();
        Camera(int width, int height, glm::vec3 position);

        glm::vec3 getPosition();
        glm::vec3 getFront();
        glm::vec3 getRight();
        glm::vec3 getUp();
        
        float getFOV();
        float getNearPlane();
        float getFarPlane();
        float getSensitivity();

        void update(Player* player);

        void matrixVoxel(Chunk chunk, Block block, Shader& shader);
        void matrix(Chunk chunk, Shader& shader, const char* uniform);
        void matrixCursor(Shader& shader, const char* uniform);
        void inputs(GLFWwindow* window, float deltaTime);
};

#endif