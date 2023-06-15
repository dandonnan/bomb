#include <string>

#ifndef GameEvent_H
#define GameEvent_H

// A game event that can be triggered with
// the EventManager.
class GameEvent{
    public:
        GameEvent(std::string name);
        ~GameEvent();

        std::string GetName();

        bool Expired();

    private:
        std::string name;

        int cycles;
};

#endif // GameEvent_H