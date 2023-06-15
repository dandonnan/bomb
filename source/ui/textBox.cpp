#include "../../include/ui/textBox.h"

#include "../../include/system/gameFactory.h"

#include "../../include/graphics/colours.h"

/// @brief Create a text box.
/// @param text The text to display.
/// @param position The position of the box.
TextBox::TextBox(std::string text, Vector2* position)
{
    background = GameFactory::GetSprite(UIFile, "TextBox", new Vector2(position->X(), position->Y()));

    this->text = GameFactory::GetText(text, 70, new Vector2(position->X() + 10, position->Y() + 15), Colours::Black);
}

/// @brief Destroy the text box.
TextBox::~TextBox()
{
    delete background;

    delete text;
}

/// @brief Update the text in the box.
/// @param text The new text.
void TextBox::UpdateText(std::string text)
{
    this->text->UpdateText(text);
}

/// @brief Draw the text box.
void TextBox::Draw()
{
    background->Draw();

    text->Draw();
}