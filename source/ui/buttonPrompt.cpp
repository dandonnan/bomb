#include "../../include/ui/buttonPrompt.h"

#include "../../include/system/gameFactory.h"

/// @brief Create a button prompt.
/// @param prompt The text on the prompt.
/// @param icon The button icon.
/// @param position The position to draw the prompt.
ButtonPrompt::ButtonPrompt(std::string prompt, std::string icon, Vector2* position)
{
    background = GameFactory::GetSprite(UIFile, "PromptBackground", position);

    button = GameFactory::GetSprite(UIFile, icon, new Vector2(position->X() + 10, position->Y() + 9));

    text = GameFactory::GetText(prompt, 70, new Vector2(position->X() + 110, position->Y() + 15));
}

/// @brief Destroy the button prompt.
ButtonPrompt::~ButtonPrompt()
{
    delete background;
    delete button;

    delete text;
}

/// @brief Draw the button prompt.
void ButtonPrompt::Draw()
{
    background->Draw();
    button->Draw();

    text->Draw();
}