#include "../../include/graphics/displayText.h"

#include "../../include/system/sdlLibrary.h"

/// @brief Create some text to draw to the screen.
/// @param text The string to draw.
/// @param size The size of the font.
/// @param colour The colour of the font.
/// @param pos The position to draw at.
DisplayText::DisplayText(std::string text, int size, SDL_Color colour, Vector2* pos)
{
    // Create a new font, or load an existing one of the same size, from the library
    font = SDLLibrary::GetInstance()->GetFont(size);
    
    this->colour = colour;

    renderer = SDLLibrary::GetInstance()->GetRenderer();
    
    // Create a surface using the string and the font
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), colour);

    // Create a texture from the surface
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    position = {pos->X(), pos->Y(), surface->w, surface->h};

    // Get rid of the surface as it is no longer required
    SDL_FreeSurface(surface);

    delete pos;
}

/// @brief Destroy the text.
DisplayText::~DisplayText()
{
    SDL_DestroyTexture(texture);
}

/// @brief Update the string that is shown.
/// @param text The new string. 
void DisplayText::UpdateText(std::string text)
{
    // Create a new surface
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), colour);

    // Get the old texture to destroy it
    SDL_Texture *oldTexture = texture;

    // Create a new texture
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    position = {position.x, position.y, surface->w, surface->h};

    // Get rid of the surface and texture that are no longer required
    SDL_FreeSurface(surface);

    SDL_DestroyTexture(oldTexture);
}

/// @brief Center the text within bounds.
/// @param bounds The bounds.
void DisplayText::Center(SDL_Rect bounds)
{
    int x = bounds.x + ((bounds.w - position.w) / 2);
    int y = bounds.y + ((bounds.h - position.h) / 2);

    position = {x, y, position.w, position.h};
}

// Draw the text
void DisplayText::Draw()
{
    if (texture)
    {
        SDL_RenderCopy(renderer, texture, NULL, &position);
    }
}