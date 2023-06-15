#include "../graphics/vector2.h"

#include <SDL.h>
#include <SDL_image.h>

#include <string>

#ifndef Sprite_H
#define Sprite_H

// Definition for a sprite.
class Sprite
{
    public:
        Sprite(std::string file, Vector2 *position);
        Sprite(std::string file, Vector2 *position, SDL_Rect source);
        ~Sprite();

        void SetPosition(Vector2 *position);

        void Update();

        void Draw();
        void Draw(Vector2 *position);

        Vector2 *GetPosition();
        SDL_Rect GetRectangle();
        int GetWidth();
        int GetHeight();

    private:
        SDL_Texture *image;
        SDL_Rect imagePosition;
        SDL_Rect sourcePosition;
        SDL_Renderer *renderer;

        Vector2* screenPosition;
};

#endif // Sprite_H