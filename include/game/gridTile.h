#include "../graphics/sprite.h"
#include "../graphics/vector2.h"

#include "tileState.h"
#include "tileValue.h"

#include <string>

#define TileWidth       150     // The width of a tile.
#define TileHeight      150     // The height of a tile.

#define TotalMarkings   4       // The total number of markers on a tile.

#ifndef GridTile_H
#define GridTile_H

// A tile displayed in the grid.
class GridTile
{
    public:
        GridTile(Vector2* position);
        ~GridTile();

        Vector2 *GetPosition();

        bool IsMarked(int marking);
        bool IsFlipped();
        bool IsComplete();

        void SetValue(TileValue value);
        TileValue GetValue();

        void ToggleMark(TileValue value);

        void Highlight(bool highlight = true);

        void Reset();
        void Flip(bool withSound = true);

        bool IsTouched();

        void Update();

        void Draw();

    private:
        Sprite *background;
        Sprite *highlight;
        Sprite *valueIcon;

        Vector2 *position;

        bool isHighlighted;

        TileState state;

        TileValue value;

        bool markings[TotalMarkings];

        Sprite *markerIcons[TotalMarkings];

        void SetupMarkings();

        void ResetBackground(std::string newBackground);
        void ResetMarkings();

        void HandleMarking();
};

#endif // GridTile_H