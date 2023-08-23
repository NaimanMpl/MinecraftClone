#include "sprite.h"

void update(Sprite* sprite) {
    sprite->tick++;
    if (sprite->tick >= ANIMATION_SPEED) {
        if (sprite->currentFrame + 1 < sprite->frameLength) {
            sprite->currentFrame++;
        } else {
            sprite->currentFrame = 0;
        }
        sprite->tick = 0;
    }
}