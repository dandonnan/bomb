#include "../../include/graphics/sprite.h"

#include "../../include/system/gameFactory.h"

#include "../../include/system/sdlLibrary.h"

/// @brief Create a new sprite using an entire texture as the image.
/// @param file The name of the texture file.
/// @param position The position to place the sprite.
Sprite::Sprite(std::string file, Vector2* position)
{
    screenPosition = new Vector2(position->X(), position->Y());

    // Either create a new surface, or get an existing one for this file from the library
    SDL_Surface *img = SDLLibrary::GetInstance()->GetSurface(file);

    if (img)
    {
        // Get the bounds where the image will be drawn on screen
        imagePosition = {position->X(), position->Y(), img->w, img->h};

        // Create a new texture, or get an existing one for this file, from the library
        image = SDLLibrary::GetInstance()->GetTexture(file);

        this->renderer = SDLLibrary::GetInstance()->GetRenderer();

        sourcePosition = {0, 0, img->w, img->h};
    }
}

/// @brief Create a new sprite that uses a specific part of an image.
/// @param file The name of the texture file.
/// @param position The position to place the sprite.
/// @param source The bounds on the texture to use as the sprite.
Sprite::Sprite(std::string file, Vector2* position, SDL_Rect source)
{
    screenPosition = new Vector2(position->X(), position->Y());

    // Either create a new surface, or get an existing one for this file from the library
    SDL_Surface *img = SDLLibrary::GetInstance()->GetSurface(file);

    if (img)
    {
        // Get the bounds where the image will be drawn on screen
        imagePosition = {position->X(), position->Y(), source.w, source.h};

        // Create a new texture, or get an existing one for this file, from the library
        image = SDLLibrary::GetInstance()->GetTexture(file);

        this->renderer = SDLLibrary::GetInstance()->GetRenderer();
        sourcePosition = source;
    }
}

/// @brief Destroy the sprite.
Sprite::~Sprite()
{
    delete screenPosition;
}

/// @brief Set the position of the sprite.
/// @param position The new position.
void Sprite::SetPosition(Vector2* position)
{
    imagePosition = {position->X(), position->Y(), imagePosition.w, imagePosition.h};
}

/// @brief Get the position of the sprite.
/// @return The sprite's position.
Vector2* Sprite::GetPosition()
{
    return screenPosition;
}

/// @brief Get the sprite's bounds.
/// @return The sprite's bounds.
SDL_Rect Sprite::GetRectangle()
{
    return imagePosition;
}

/// @brief Get the width of the sprite.
/// @return The width of the sprite.
int Sprite::GetWidth()
{
    return sourcePosition.w;
}

/// @brief Get the height of the sprite.
/// @return The height of the sprite.
int Sprite::GetHeight()
{
    return sourcePosition.h;
}

/// @brief Update the sprite.
void Sprite::Update()
{
}

/// @brief Draw the sprite.
void Sprite::Draw()
{
    SDL_RenderCopy(renderer, image, &sourcePosition, &imagePosition);
}

/// @brief Draw the sprite at the given position.
/// @param position The position to draw the sprite.
void Sprite::Draw(Vector2 *position)
{
    SDL_Rect pos = {position->X(), position->Y(), imagePosition.w, imagePosition.h};

    SDL_RenderCopy(renderer, image, &sourcePosition, &pos);
}