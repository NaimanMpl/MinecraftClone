#ifndef FRUSTRUM_CULLING_CLASS_H
#define FRUSTRUM_CULLING_CLASS_H

#include "camera.h"

class FrustrumCulling {
    private:
        Camera* camera;
        float yFactor, xFactor, tanY, tanX;
    public:
        FrustrumCulling();
        FrustrumCulling(Camera* camera);

        bool isVisible(Chunk* chunk);
};

#endif