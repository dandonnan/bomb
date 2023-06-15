#include <SDL.h>

#ifndef Colours_H
#define Colours_H

// Definitions for colours
struct Colours
{
    public:
        static constexpr SDL_Color White = {255, 255, 255, 0};
        static constexpr SDL_Color Black = {0, 0, 0, 0};
};

#endif // Colours_H