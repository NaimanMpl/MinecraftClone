#ifndef HAND_CLASS_H
#define HAND_CLASS_H

#include <glm/glm.hpp>

enum HandAnimation { Idle = 0, Moving = 1 };

struct ViewBobbing {
    float sinTime;
    float effectSpeed;
    float effecIntensity;
    float effectIntensityX;
    glm::vec3 position;
    float y;
};

static const unsigned int ANIMATION_SPEED = 10;

class Hand {
    private:
        unsigned int animationTick;
        float animationState;
        HandAnimation animation;
        ViewBobbing* viewBobbing;

    public:
        Hand();
        
        void update(glm::vec3 cameraRight, glm::vec3 velocity);

        HandAnimation getAnimation();
        void setAnimation(HandAnimation animation);
        float getAnimationState();
        ViewBobbing* getViewBobbing();
};

#endif