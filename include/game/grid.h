#include "gridTile.h"
#include "headerTile.h"
#include "gridColours.h"

#include "tileValue.h"

#include "../graphics/vector2.h"

#include "../graphics/displayText.h"

#include <string>
#include <vector>

#define TileOffset      20      // The offset between tiles
#define ConnectorOffset 63      // The offset between the edge of a tile and the connector

#ifndef Grid_H
#define Grid_H

// The puzzle grid.
// This also handles the tiles on the edge of the grid
// and the connectors between the tiles.
class Grid
{
    public:
        Grid(int size);
        ~Grid();

        void Reset(int level);

        GridTile *GetCurrentTile();

        void FlipAll();

        void Update();
        void UpdateInMarkerMode();

        void Draw();

    private:
        int size;
        GridTile* tiles[5][5];

        std::vector<HeaderTile*> headers;
        std::vector<Sprite*> connectors;

        int tileX;
        int tileY;

        void Setup3x3();
        void Setup4x4();
        void Setup5x5();

        void SetupGrid(int size, Vector2* position);

        void PlaceHeaders(Vector2* position);
        void PlaceConnectors(Vector2* position);
        void PlaceTiles(Vector2* position);

        void HandleMovement();
        void HandleFlip();
        void HandleTouchInput(bool markOnly = false);

        void CheckForGridCompletion();

        void GenerateGridValues(int level);
        void PlaceValuesInGrid(TileValue value, int amount, int excludeRow = -1, int excludeColumn = -1);
        void SetValuesInHeaders();

        std::string GetConnectorSpriteName(GridColours colour, bool vertical);
};

#endif // Grid_H