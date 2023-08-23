#ifndef SPRITE_CLASS_H
#define SPRITE_CLASS_H

#include <vector>
#include "world/material.h"

static const unsigned int ANIMATION_SPEED = 15;

struct Sprite {
    unsigned int tick;
    unsigned int currentFrame;
    int frameLength;
    glm::vec2 position;
    glm::vec2 size;
};

void update(Sprite* sprite);

#endif