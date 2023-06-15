#ifndef PlayState_H
#define PlayState_H

// States the game can be in on the grid screen.
enum PlayState
{
    Playing = 0,
    Marking = 1,
    Paused = 2,
    GameOver = 3,
};

#endif // PlayState_H