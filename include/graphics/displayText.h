#include "vector2.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

#ifndef DisplayText_H
#define DisplayText_H

// Text that is displayed on screen.
class DisplayText
{
    public:
        DisplayText(std::string text, int size, SDL_Color colour, Vector2 *pos);
        ~DisplayText();

        void UpdateText(std::string text);

        void Center(SDL_Rect bounds);

        void Draw();

    private:
        SDL_Texture *texture;
        SDL_Rect position;

        SDL_Renderer *renderer;

        TTF_Font* font;
        SDL_Color colour;
};

#endif // DisplayText_H