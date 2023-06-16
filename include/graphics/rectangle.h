#include "vector2.h"

#include <SDL.h>

#ifndef Rectangle_H
#define Rectangle_H

// A definition for a rectangle.
class Rectangle
{
    public:
        Rectangle();
        Rectangle(int x, int y, int w, int h);
        Rectangle(SDL_Rect rectangle);
        ~Rectangle();

        int X();
        int Y();
        int Width();
        int Height();

        bool Contains(Vector2* point);

        void Move(Vector2 *position);

    private:
        Vector2 *position;
        int width;
        int height;
};

#endif // Rectangle_H