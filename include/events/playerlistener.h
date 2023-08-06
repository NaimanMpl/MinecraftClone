#ifndef PLAYER_LISTENER_H
#define PLAYER_LISTENER_H

#include "playereventlistener.h"

class PlayerListener: public PlayerEventListener {
    void onBreakBlock(BlockBreakEvent* event);
};

#endif