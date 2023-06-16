#include "../graphics/sprite.h"
#include "../graphics/displayText.h"
#include "../graphics/vector2.h"

#include <string>

#ifndef ButtonPrompt_H
#define ButtonPrompt_H

// A button prompt, with text.
class ButtonPrompt
{
    public:
        ButtonPrompt(std::string prompt, std::string icon, Vector2* position);
        ~ButtonPrompt();

        bool IsTouched();

        void Draw();

    private:
        Sprite *background;
        Sprite *button;

        DisplayText *text;
};

#endif // ButtonPrompt_H