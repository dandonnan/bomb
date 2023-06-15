#include "../../include/system/dataReader.h"
#include "../../include/system/gameFactory.h"
#include "../../include/graphics/displayText.h"
#include "../../include/graphics/colours.h"
#include "../../include/graphics/sprite.h"

GameFactory *GameFactory::instance{nullptr};

/// @brief Get the instance of the game factory.
/// @return The game factory instance.
GameFactory *GameFactory::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new GameFactory();
    }

    return instance;
}

/// @brief Initialise the game factory.
/// @param renderer The SDL renderer.
void GameFactory::Initialise(SDL_Renderer* renderer)
{
    GetInstance();

    instance->renderer = renderer;

    // Read data files containing text and sprite setup
    instance->localisation = DataReader::ReadFileAsMap("data/text/en/general.json");
    instance->spriteConfig = DataReader::ReadFileAsMap("data/images/spritesConfig.json");
}

/// @brief Create an object to display text on screen.
///        This uses a default font size.
/// @param text The string to draw.
/// @param position The position to draw the string.
/// @return A display text object.
DisplayText* GameFactory::GetText(std::string text, Vector2* position)
{
    return GetText(text, 36, position);
}

/// @brief Create an object to display text on screen.
/// @param text The string to draw.
/// @param size The size of the font.
/// @param position The position to draw the string.
/// @return A display text object.
DisplayText* GameFactory::GetText(std::string text, int size, Vector2* position)
{
    return new DisplayText(text, size, Colours::White, position);
}

/// @brief Create an object to display text on screen.
/// @param text The string to draw.
/// @param size The size of the font.
/// @param position The position to draw the string.
/// @param colour The colour of the text.
/// @return A display text object.
DisplayText *GameFactory::GetText(std::string text, int size, Vector2 *position, SDL_Color colour)
{
    return new DisplayText(text, size, colour, position);
}

/// @brief Create a sprite object.
/// @param file The texture file.
/// @param position The position to draw the sprite.
/// @return A sprite object.
Sprite* GameFactory::GetSprite(std::string file, Vector2* position)
{
    return new Sprite(file, position);
}

/// @brief Create a sprite object.
/// @param file The texture file.
/// @param id The id of a sprite in the sprites config file.
/// @param position The position to draw the sprite.
/// @return A sprite object.
Sprite* GameFactory::GetSprite(std::string file, std::string id, Vector2* position)
{
    // Get the rectangle for the sprite which is set with the given id in the
    // sprites config file
    SDL_Rect rect = DataReader::ParseRectangleFromString(instance->spriteConfig[id]);

    return new Sprite(file, position, rect);
}

/// @brief Get a localised string.
/// @param key The key of the string in the text file.
/// @return The localised string.
std::string GameFactory::GetLocalisedString(std::string key)
{
    return instance->localisation[key];
}