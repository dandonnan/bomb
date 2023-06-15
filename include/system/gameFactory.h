#include "../graphics/sprite.h"
#include "../graphics/displayText.h"
#include "../graphics/vector2.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <map>

#define UIFile "data/images/ui.png"     // The file with the game's UI images.

#ifndef GameFactory_H
#define GameFactory_H

// A factory for creating game objects.
class GameFactory
{
    public:
        static GameFactory *GetInstance();

        GameFactory(GameFactory &other) = delete;
        void operator=(const GameFactory &) = delete;

        static void Initialise(SDL_Renderer *renderer);

        static DisplayText* GetText(std::string text, Vector2* position);
        static DisplayText *GetText(std::string text, int size, Vector2* position);
        static DisplayText *GetText(std::string text, int size, Vector2 *position, SDL_Color colour);
        static Sprite *GetSprite(std::string file, Vector2 *position);
        static Sprite *GetSprite(std::string file, std::string id, Vector2 *position);
        static std::string GetLocalisedString(std::string key);

    protected:
        GameFactory() {}
        ~GameFactory() {}

    private:
        static GameFactory *instance;

        SDL_Renderer *renderer;

        std::map<std::string, std::string> localisation;
        std::map<std::string, std::string> spriteConfig;
};

#endif // GameFactory_H