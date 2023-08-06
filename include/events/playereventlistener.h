#ifndef PLAYER_EVENT_LISTENER_INTERFACE_H
#define PLAYER_EVENT_LISTENER_INTERFACE_H

#include "blockbreakevent.h"

class PlayerEventListener {
    public:
        virtual void onBreakBlock(BlockBreakEvent* event);
};

#endif