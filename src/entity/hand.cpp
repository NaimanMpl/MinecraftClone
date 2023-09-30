#include "entity/hand.h"

Hand::Hand() {
    animation = HandAnimation::Idle;
    viewBobbing = new ViewBobbing{0.0f, 8.0f, 0.1f, 0.3f, glm::vec3(0.0f), 0.0f};
}


void Hand::update(glm::vec3 cameraRight, float deltaTime, glm::vec3 velocity) {

    if (animation == HandAnimation::Moving) {
        float magnitude = sqrt(pow(velocity.x, 2.0f) + pow(velocity.y, 2.0f) + pow(velocity.z, 2.0f));

        if (magnitude > 0.0f) {
            viewBobbing->sinTime += deltaTime * viewBobbing->effectSpeed;
        } else {
            viewBobbing->sinTime = 0.0f;
        }

        viewBobbing->y = -abs(viewBobbing->effecIntensity * sin(viewBobbing->sinTime));
        viewBobbing->position = cameraRight * viewBobbing->effecIntensity * float(cos(viewBobbing->sinTime)) * viewBobbing->effectIntensityX;
    } else {
        viewBobbing->position *= 0.95f;
        viewBobbing->y *= 0.95f;
    }

    animationTick++;

    if (animationTick > ANIMATION_SPEED) {
        animationState += 0.01f;
        if (animationState > 0.08f) animationState = 0.0f;
        animationTick = 0;
    }
}

HandAnimation Hand::getAnimation() {
    return this->animation;
}

void Hand::setAnimation(HandAnimation animation) {
    this->animation = animation;
}

float Hand::getAnimationState() {
    return this->animationState;
}

ViewBobbing* Hand::getViewBobbing() {
    return this->viewBobbing;
}