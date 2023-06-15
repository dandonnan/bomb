#include "../graphics/sprite.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <string>
#include <map>

#ifndef SDLLibrary_H
#define SDLLibrary_H

// A library for getting resources using SDL.
// Starting a 5x5 grid used to take ~6+ seconds because almost
// 300 calls were being done where a lot of the same resources
// would be loaded and disposed (this is what happens when
// you try to scale up from a simple tutorial).
// This library will cache resources so that once they are
// loaded they are permanently in memory (until Clear is called).
class SDLLibrary
{
    public:
        static SDLLibrary *GetInstance();

        SDLLibrary(SDLLibrary &other) = delete;
        void operator=(const SDLLibrary &) = delete;

        static void Initialise(SDL_Renderer *renderer);

        static void Clear();

        static SDL_Renderer *GetRenderer();

        static SDL_Surface *GetSurface(std::string name);
        static SDL_Texture *GetTexture(std::string name);
        static TTF_Font *GetFont(int size);

        static Mix_Music *GetMusic(std::string name);
        static Mix_Chunk *GetSound(std::string name);

    protected:
        SDLLibrary() { }
        ~SDLLibrary() { }

    private:
        static SDLLibrary *instance;

        SDL_Renderer *renderer;

        std::map<std::string, SDL_Surface*> surfaces;
        std::map<std::string, SDL_Texture*> textures;
        std::map<int, TTF_Font*> fonts;

        std::map<std::string, Mix_Music*> music;
        std::map<std::string, Mix_Chunk*> sounds;
};

#endif // SDLLibrary_H