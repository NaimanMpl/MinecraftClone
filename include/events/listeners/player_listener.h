#ifndef PLAYER_LISTENER_CLASS_H
#define PLAYER_LISTENER_CLASS_H

#include "event_listener.h"

class PlayerListener: public EventListener {
    public:
        PlayerListener();
        void onBlockBreak(BlockBreakEvent* event);
};

#endif