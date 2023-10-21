#ifndef EVENT_LISTENER_CLASS_H
#define EVENT_LISTENER_CLASS_H

#include "../blockbreakevent.h"
#include "../blockplaceevent.h"

class EventListener {
    public:
        virtual void onBlockBreak(BlockBreakEvent* event) = 0;
        virtual void onBlockPlace(BlockPlaceEvent* event) = 0;

};

#endif