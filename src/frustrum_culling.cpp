#include "frustrum_culling.h"

FrustrumCulling::FrustrumCulling() {

}

FrustrumCulling::FrustrumCulling(Camera* camera) {
    this->camera = camera;

    this->yFactor = 1.0f / cos(glm::radians(camera->getFOV()) / 2.0f);
    this->tanY = tan(glm::radians(camera->getFOV()) / 2.0f);
    float hFOV = 2 * atan(tan(glm::radians(camera->getFOV()) * 0.5f) * (float) GameConfiguration::WINDOW_WIDTH / GameConfiguration::WINDOW_HEIGHT);
    this->xFactor = 1.0f / cos(hFOV / 2.0f);
    this->tanX = tan(hFOV);
}

bool FrustrumCulling::isVisible(Chunk* chunk) {

    glm::vec3 chunkCenter = glm::vec3(glm::vec3(chunk->getPosition()) + 0.5f) * float(CHUNK_SIZE);
    glm::vec3 sphereVector = chunkCenter - camera->getPosition();

    float sz = glm::dot(sphereVector, camera->getFront());

    if (!(camera->getNearPlane() - CHUNK_SPHERE_RADIUS <= sz && sz <= camera->getFarPlane() + CHUNK_SPHERE_RADIUS)) {
        return false;
    }

    float sy = glm::dot(sphereVector, camera->getUp());
    float distance = yFactor * CHUNK_SPHERE_RADIUS + sz * tanY;

    if (!(-distance <= sy && sy <= distance)) {
        return false;
    }

    float sx = glm::dot(sphereVector, camera->getRight());
    distance = xFactor * CHUNK_SPHERE_RADIUS + sz * tanX;

    if (!(-distance <= sx && sx <= distance)) {
        return false;
    }

    return true;
}