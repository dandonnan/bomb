#include "../graphics/sprite.h"
#include "../graphics/rectangle.h"

#include <functional>

#ifndef Button_H
#define Button_H

// A button on screen.
class Button
{
    public:
        Button(Sprite *icon, std::function<void()> onSelected, Sprite *highlight);
        virtual ~Button();
        void Highlight(bool highlight = true);
        void Select();
        bool IsTouched();
        virtual void Update();
        virtual void Draw();

    protected:
        Sprite *icon;
        Sprite *highlight;
        Rectangle *bounds;
        bool highlighted;
        std::function<void()> onSelected;
};

#endif // Button_H