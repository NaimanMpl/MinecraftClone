#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H

#include "../ray.h"
#include "entity.h"
#include "hand.h"
#include "inventory/hotbar.h"
#include <GLFW/glfw3.h>

enum GameMode { CREATIVE, SURVIVAL };

class Player: public Entity {
    private:
        Hotbar hotbar;
        GameMode gameMode;
        Ray ray;
        Hand hand;
        float mouseX, mouseY, mouseOffsetX, mouseOffsetY, lastMouseX, lastMouseY;
        float fov;
        float maxSprintSpeed;
        float baseSpeed;
        bool firstMouse, sneaking, breakingBlock;
        bool moving;
        bool sprinting;
        
        void handleCollisions(glm::vec3 newVelocity);
    public:
        Player();
        Player(glm::vec3 position);

        Ray& getRay();
        Hand& getHand();
        Hotbar& getHotbar();

        bool isImmobile();
        bool isSneaking();
        bool isBreakingBlock();
        bool isSprinting();
        
        void setBreakingBlock(bool breakingBlock);
        void breakBlock(Chunk* chunk, int worldX, int worldY, int worldZ, int8_t block);
        void handleInputs(GLFWwindow* window, float deltaTime);
        void update(float deltaTime);
};

#endif