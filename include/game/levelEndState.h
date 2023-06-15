#ifndef LevelEndState_H
#define LevelEndState_H

// The states for when a level is over.
// Reveal all tiles, display a message, then reset.
enum LevelEndState
{
    Reveal = 0,
    Message = 1,
    Reset = 2
};

#endif // LevelEndState_H