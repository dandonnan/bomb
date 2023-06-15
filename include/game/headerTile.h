#include "../graphics/sprite.h"
#include "../graphics/vector2.h"
#include "../graphics/displayText.h"
#include "gridColours.h"

#include <string>

#ifndef HeaderTile_H
#define HeaderTile_H

// A tile displayed at the edge of the grid.
class HeaderTile
{
    public:
        HeaderTile(GridColours colour, Vector2* position);
        ~HeaderTile();

        void SetValue(int value, int bombs);

        void Draw();

    private:
        Sprite *background;
        Sprite *bombIcon;

        DisplayText *numberOfBombs;
        DisplayText *values;

        std::string GetSpriteName(GridColours colour);
};

#endif // HeaderTile_H