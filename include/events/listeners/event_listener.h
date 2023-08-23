#ifndef EVENT_LISTENER_CLASS_H
#define EVENT_LISTENER_CLASS_H

#include "../blockbreakevent.h"

class EventListener {
    public:
        virtual void onBlockBreak(BlockBreakEvent* event) = 0;

};

#endif