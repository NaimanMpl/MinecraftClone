#include "frustrum_culling.h"
#include "game.h"

FrustrumCulling::FrustrumCulling() {

}

FrustrumCulling::FrustrumCulling(Camera* camera) {
    this->camera = camera;

    float halfY = glm::radians(camera->getFOV() / 2.0f);
    this->yFactor = 1.0f / cos(halfY);
    this->tanY = tan(halfY);

    float aspectRatio = (float) GameConfiguration::WINDOW_WIDTH / GameConfiguration::WINDOW_HEIGHT;
    float halfX = atan(this->tanY * aspectRatio);

    this->xFactor = 1.0f / cos(halfX);
    this->tanX = tan(halfX);
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

bool FrustrumCulling::outOfView(int chunkX, int chunkY, int chunkZ) {
    Player& player = Game::getInstance().getPlayer();
    int startX = std::max(0, int(player.getPosition().x / CHUNK_SIZE - Game::CHUNK_RENDER_DISTANCE));
    int startZ = std::max(0, int(player.getPosition().z / CHUNK_SIZE - Game::CHUNK_RENDER_DISTANCE));

    int endX = player.getPosition().x / CHUNK_SIZE + Game::CHUNK_RENDER_DISTANCE;
    int endZ = player.getPosition().z / CHUNK_SIZE + Game::CHUNK_RENDER_DISTANCE;
    return chunkX < startX || chunkZ < startZ || chunkX > endX || chunkZ > endZ;
}