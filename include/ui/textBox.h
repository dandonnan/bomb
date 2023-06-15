#include "../graphics/vector2.h"
#include "../graphics/sprite.h"
#include "../graphics/displayText.h"

#include <string>

#ifndef TextBox_H
#define TextBox_H

// A text box with a background.
class TextBox
{
    public:
        TextBox(std::string text, Vector2* position);
        ~TextBox();

        void UpdateText(std::string text);

        void Draw();

    private:
        Sprite *background;
        DisplayText *text;
};

#endif // TextBox_H