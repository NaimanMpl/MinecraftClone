#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include "../ray.h"
#include "entity.h"
#include <GLFW/glfw3.h>

enum GameMode { CREATIVE, SURVIVAL };

class Player: public Entity {
    private:
        GameMode gameMode;
        Ray ray;
        float mouseX, mouseY, mouseOffsetX, mouseOffsetY, lastMouseX, lastMouseY;
        bool firstMouse, sneaking, breakingBlock;

        bool collide(glm::vec3 position);
    public:
        Player();
        Player(glm::vec3 position);


        Ray& getRay();
        bool isImmobile();
        bool isSneaking();
        bool isBreakingBlock();
        
        void setBreakingBlock(bool breakingBlock);
        void breakBlock(Chunk* chunk, Block* block);
        void handleInputs(GLFWwindow* window, float deltaTime);
        void update(float deltaTime);
        bool collideWithWorld(glm::vec3 newPosition);
};

#endif