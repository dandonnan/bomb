#include "../../include/events/gameEvent.h"

/// @brief Create a new game event with the given name.
/// @param name The name of the event.
GameEvent::GameEvent(std::string name)
{
    this->name = name;
    cycles = 0;
}

/// @brief Destroy the game event.
GameEvent::~GameEvent()
{
}

/// @brief Get the name of the event.
/// @return The event's name.
std::string GameEvent::GetName()
{
    return name;
}

/// @brief Get whether the event has expired.
///        This also effectively acts as an update method
///        by incrementing the number of cycles the event
///        has been active for.
/// @return true if the event has expired. false if not.
bool GameEvent::Expired()
{
    if (cycles > 1)
    {
        return true;
    }

    cycles++;

    return false;
}