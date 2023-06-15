#include "../../include/ui/menuOption.h"

#include "../../include/system/gameFactory.h"

/// @brief Create a menu option.
/// @param text The text on the option.
/// @param position The position to draw the option.
/// @param onSelected The function to call when the option is selected.
MenuOption::MenuOption(std::string text, Vector2* position, std::function<void()> onSelected)
    : Button(GameFactory::GetSprite(UIFile, "MenuOption", position), onSelected, GameFactory::GetSprite(UIFile, "HighlightedOption", position))
{
    this->text = GameFactory::GetText(text, 80, new Vector2(position->X() + 120, position->Y() + 25));

    this->text->Center(icon->GetRectangle());

    delete position;
}

/// @brief Create a menu option with a font size.
/// @param text The text on the option.
/// @param fontSize The size of the text.
/// @param position The position to draw the option.
/// @param onSelected The function call when the option is selected.
MenuOption::MenuOption(std::string text, int fontSize, Vector2* position, std::function<void()> onSelected)
    : Button(GameFactory::GetSprite(UIFile, "MenuOption", position), onSelected, GameFactory::GetSprite(UIFile, "HighlightedOption", position))
{
    this->text = GameFactory::GetText(text, fontSize, new Vector2(position->X() + 120, position->Y() + 25));

    this->text->Center(icon->GetRectangle());

    delete position;
}

/// @brief Destroy the menu option.
MenuOption::~MenuOption()
{
    delete text;
}

/// @brief Draw the option.
void MenuOption::Draw()
{
    Button::Draw();

    text->Draw();
}