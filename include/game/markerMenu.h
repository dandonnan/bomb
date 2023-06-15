#include "../graphics/sprite.h"
#include "../graphics/vector2.h"

#include "gridTile.h"

#ifndef MarkerMenu_H
#define MarkerMenu_H

// A menu for marking a tile with possible values.
class MarkerMenu
{
    public:
        MarkerMenu();
        ~MarkerMenu();

        void SetTile(GridTile *gridTile);

        void Update();
        void Draw();

    private:
        Sprite *background;

        Sprite *selector;
        Vector2 *selectorPosition;

        GridTile *gridTile;

        Sprite *markerHighlight;

        Sprite *tiles[TotalMarkings];

        int selectedTile;

        Vector2 *GetSelectorPosition();
};

#endif // MarkerMenu_H