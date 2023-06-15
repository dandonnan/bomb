#include "../../include/system/sdlLibrary.h"

SDLLibrary *SDLLibrary::instance{nullptr};

/// @brief Get the instance of the SDL library.
/// @return The SDL library instance.
SDLLibrary *SDLLibrary::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new SDLLibrary();
    }

    return instance;
}

/// @brief Initialise the library.
/// @param renderer The SDL renderer.
void SDLLibrary::Initialise(SDL_Renderer* renderer)
{
    GetInstance();

    instance->renderer = renderer;
}

/// @brief Clear the library, disposing everything currently in it.
void SDLLibrary::Clear()
{
    // Free all surfaces
    for (std::map<std::string, SDL_Surface*>::iterator it = instance->surfaces.begin(); it != instance->surfaces.end(); it++)
    {
        SDL_FreeSurface(it->second);
    }

    // Destroy all textures
    for (std::map<std::string, SDL_Texture*>::iterator it = instance->textures.begin(); it != instance->textures.end(); it++)
    {
        SDL_DestroyTexture(it->second);
    }

    // Remove all fonts
    for (std::map<int, TTF_Font*>::iterator it = instance->fonts.begin(); it != instance->fonts.end(); it++)
    {
        TTF_CloseFont(it->second);
    }

    // Unload all music
    for (std::map<std::string, Mix_Music*>::iterator it = instance->music.begin(); it != instance->music.end(); it++)
    {
        Mix_FreeMusic(it->second);
    }

    // Unload all music
    for (std::map<std::string, Mix_Chunk*>::iterator it = instance->sounds.begin(); it != instance->sounds.end(); it++)
    {
        Mix_FreeChunk(it->second);
    }

    instance->surfaces.clear();
    instance->textures.clear();
    instance->fonts.clear();

    instance->music.clear();
    instance->sounds.clear();
}

/// @brief Get the renderer.
/// @return The renderer.
SDL_Renderer* SDLLibrary::GetRenderer()
{
    return instance->renderer;
}

/// @brief Load a surface from the name of a texture file.
///        If the surface has already been loaded, it will
///        return it. Otherwise the surface will be loaded.
/// @param name The name of the texture to load.
/// @return The surface.
SDL_Surface* SDLLibrary::GetSurface(std::string name)
{
    if (instance->surfaces.count(name) > 0)
    {
        return instance->surfaces[name];
    }

    SDL_Surface *img = IMG_Load(name.c_str());

    instance->surfaces.insert(std::pair<std::string, SDL_Surface*>(name, img));
    instance->textures.insert(std::pair<std::string, SDL_Texture*>(name, SDL_CreateTextureFromSurface(instance->renderer, img)));

    return img;
}

/// @brief Load a texture with the given name.
///        If the texture has already been loaded, it will
///        return it. Otherwise, both it and the surface
///        will be loaded.
/// @param name The name of the texture file.
/// @return The texture.
SDL_Texture* SDLLibrary::GetTexture(std::string name)
{
    if (instance->textures.count(name) > 0)
    {
        return instance->textures[name];
    }

    GetSurface(name);

    return instance->textures[name];
}

/// @brief Load a font with the given size.
///        If the font has previously been loaded with
///        that size, it will be returned. Otherwise the
///        font will be loaded.
/// @param size The size of the font.
/// @return The font.
TTF_Font* SDLLibrary::GetFont(int size)
{
    if (instance->fonts.count(size) > 0)
    {
        return instance->fonts[size];
    }

    instance->fonts.insert(std::pair<int, TTF_Font*>(size, TTF_OpenFont("data/fonts/Oxanium-Light.ttf", size)));

    return instance->fonts[size];
}

/// @brief Load a background music track with the
///        given name.
///        If the track has previously been loaded, it
///        will be returned. Otherwise the track will
///        be loaded.
/// @param name The name of the track.
/// @return The music track.
Mix_Music* SDLLibrary::GetMusic(std::string name)
{
    if (instance->music.count(name) > 0)
    {
        return instance->music[name];
    }

    instance->music.insert(std::pair<std::string, Mix_Music*>(name, Mix_LoadMUS(name.c_str())));

    return instance->music[name];
}

/// @brief Load a sound effect with the given name.
///        If the sound has previously been loaded, it
///        will be returned. Otherwise the sound will
///        be loaded.
/// @param name The name of the sound effect.
/// @return The sound effect.
Mix_Chunk* SDLLibrary::GetSound(std::string name)
{
    if (instance->sounds.count(name) > 0)
    {
        return instance->sounds[name];
    }

    instance->sounds.insert(std::pair<std::string, Mix_Chunk*>(name, Mix_LoadWAV(name.c_str())));

    return instance->sounds[name];
}