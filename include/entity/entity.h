#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include <glm/glm.hpp>
#include <vector>
#include "hitbox.h"
#include "events/listeners/event_listener.h"

class Entity {
    protected:
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 acceleration;
        glm::vec3 gravity;
        Hitbox hitbox;
        std::vector<EventListener*> listeners;

        bool movingLeft, movingRight, movingForward, movingBackward;
        bool inAir;
        float speed;
        float maxSpeed;
        float yaw, pitch;
    public:

        Entity();
        Entity(glm::vec3& position);

        glm::vec3& getPosition();
        glm::vec3& getVelocity();
        glm::vec3& getAcceleration();

        Hitbox& getHitbox();

        bool isInAir();
        float getSpeed();
        float getYaw();
        float getPitch();

        void addEventListener(EventListener* listener);

        virtual void update() = 0;
};

#endif