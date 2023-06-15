#include "../../include/events/eventManager.h"

// A pointer to the event manager instance.
EventManager *EventManager::instance{nullptr};

/// @brief Get the instance of the event manager.
/// @return The event manager instance.
EventManager *EventManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new EventManager();
    }

    return instance;
}

/// @brief Updates game events registered with the event
///        manager.
void EventManager::Update()
{
    for (int i = (int)events.size() - 1; i >= 0; i--)
    {
        // If the event has expired (existed for more than
        // a few cycles / frames), then get rid of it.
        if (events.at(i)->Expired())
        {
            delete events.at(i);

            events.erase(events.begin() + i);
        }
    }
}

/// @brief Fire off an event with the given name.
/// @param name The name of the event. This should be one listed in knownEvents.h.
void EventManager::FireEvent(std::string name)
{
    // Add a new event to the list of events
    events.push_back(new GameEvent(name));
}

/// @brief Check if an event with the name has been fired, and
///        kill it if it has.
/// @param name The name of the event. This should be one listed in knownEvents.h.
/// @return true if the event has been fired. false if not.
bool EventManager::HasEventFiredThenKill(std::string name)
{
    for (int i = 0; i < (int)events.size(); i++)
    {
        if (events.at(i)->GetName() == name)
        {
            events.erase(events.begin() + i);
            return true;
        }
    }

    return false;
}