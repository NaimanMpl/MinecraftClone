#include "game_configuration.h"

namespace GameConfiguration {

    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;
    const int FPS_SET = 120;
    const int UPS_SET = 200;
    const float GAME_SCALE = 1.0f;

    const int CHUNK_SIZE = 16;
    const int CHUNK_AREA = CHUNK_SIZE * CHUNK_SIZE;
    const int CHUNK_VOL = CHUNK_AREA * CHUNK_SIZE;
    
    const int WORLD_WIDTH = 2;
    const int WORLD_HEIGHT = 2;
    const int WORLD_DEPTH = WORLD_WIDTH;
    const int WORLD_AREA = WORLD_WIDTH * WORLD_DEPTH;
    const int WORLD_VOLUME = WORLD_AREA * WORLD_HEIGHT;

    const int WORLD_CENTER_XZ = WORLD_WIDTH * (int) (CHUNK_SIZE / 2);
    const int WORLD_CENTER_Y = WORLD_HEIGHT * (int) (CHUNK_SIZE / 2);

}