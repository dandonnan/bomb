#include "../../include/ui/button.h"
#include "../../include/system/inputManager.h"

/// @brief Create a button.
/// @param icon The sprite to use as the background.
/// @param onSelected A function to call when the button is selected.
/// @param highlight The sprite to use when highlighted.
Button::Button(Sprite *icon, std::function<void()> onSelected, Sprite *highlight)
{
    this->icon = icon;

    this->onSelected = onSelected;

    this->highlight = highlight;

    highlighted = false;

    bounds = new Rectangle((int)icon->GetPosition()->X(), (int)icon->GetPosition()->Y(), icon->GetWidth(), icon->GetHeight());
}

/// @brief Destroy the button.
Button::~Button()
{
    delete icon;

    delete highlight;

    delete bounds;
}

/// @brief Highlight the button.
///        If no value is passed in, the default is true.
/// @param highlight Whether or not to highlight the button.
void Button::Highlight(bool highlight)
{
    highlighted = highlight;
}

/// @brief Select the button.
void Button::Select()
{
    // If the button has a function to call, call it
    if (onSelected != nullptr)
    {
        onSelected();
    }
}

/// @brief Get whether the button was touched.
/// @return true if touched. false if not.
bool Button::IsTouched()
{
    return InputManager::GetInstance()->IsTouched()
            && bounds->Contains(InputManager::GetInstance()->GetTouchPosition());
}

/// @brief Update the button.
void Button::Update()
{
}

/// @brief Draw the button.
void Button::Draw()
{
    icon->Draw();

    if (highlighted)
    {
        highlight->Draw();
    }
}