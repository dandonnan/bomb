#include "button.h"
#include "../graphics/displayText.h"

#include <string>

#ifndef MenuOption_H
#define MenuOption_H

// An option on a menu.
class MenuOption : public Button
{
    public:
        MenuOption(std::string text, Vector2* position, std::function<void()> onSelected);
        MenuOption(std::string text, int fontSize, Vector2 *position, std::function<void()> onSelected);
        ~MenuOption();

        void Draw() override;

    private:
        DisplayText *text;
};

#endif // MenuOption_H