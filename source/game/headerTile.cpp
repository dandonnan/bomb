#include "../../include/game/headerTile.h"

#include "../../include/system/gameFactory.h"

/// @brief Create a new header tile to display on the top / side of the grid.
/// @param colour The colour of the tile.
/// @param position The position of the tile.
HeaderTile::HeaderTile(GridColours colour, Vector2* position)
{
    // Create the background sprite at the position, using the given colour
    background = GameFactory::GetSprite(UIFile, GetSpriteName(colour), position);

    // Create a bomb icon at an offset from the position
    bombIcon = GameFactory::GetSprite(UIFile, "SideBomb", new Vector2(position->X() + 5, position->Y() + 65));
}

/// @brief Destructor called when the tile is no longer required.
HeaderTile::~HeaderTile()
{
    // Free up memory by removing the sprite and text
    delete background;
    delete bombIcon;

    delete numberOfBombs;
    delete values;
}

/// @brief Set the values on the tile.
/// @param value The total value in the row / column.
/// @param bombs The total number of bombs in the row / column.
void HeaderTile::SetValue(int value, int bombs)
{
    Vector2* position = background->GetPosition();

    // Create text displays for the values, offset from the tile's position
    numberOfBombs = GameFactory::GetText(std::to_string(bombs), 40, new Vector2(position->X() + 90, position->Y() + 90));
    values = GameFactory::GetText(std::to_string(value), 40, new Vector2(position->X() + 90, position->Y() + 10));
}

/// @brief Draw the tile.
void HeaderTile::Draw()
{
    // Draw the tile and the bomb icon
    background->Draw();
    bombIcon->Draw();

    // Draw the text
    numberOfBombs->Draw();
    values->Draw();
}

/// @brief Get the name of the sprite to use for the tile based on the colour.
/// @param colour The colour of the tile.
/// @return The name of the sprite to use.
std::string HeaderTile::GetSpriteName(GridColours colour)
{
    switch (colour)
    {
        case Red:
            return "SideRed";

        case Green:
            return "SideGreen";

        case Yellow:
            return "SideYellow";

        case Blue:
            return "SideBlue";

        case Purple:
        default:
            return "SidePurple";
    }
}
