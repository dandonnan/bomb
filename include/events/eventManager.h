#include <vector>
#include "gameEvent.h"

#ifndef EventManager_H
#define EventManager_H

// A manager for game events.
// When an event is fired (using FireEvent), it gets added
// to a list for a few frames so that objects can check if
// an event has occurred and react to it.
// This is quite limited in that only one object can react
// to a single event, and data cannot be passed as part
// of the event (like the code in Seed that this was based
// off), but they were not required.
class EventManager {
    public:
        static EventManager *GetInstance();

        EventManager(EventManager &other) = delete;
        void operator=(const EventManager &) = delete;

        void Update();

        void FireEvent(std::string name);
        bool HasEventFiredThenKill(std::string name);

    protected:
        EventManager() {}
        ~EventManager() {}

    private:
        static EventManager *instance;

        std::vector<GameEvent*> events;
};

#endif // EventManager_H