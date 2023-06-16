#include "../../include/game/grid.h"

#include "../../include/system/core.h"
#include "../../include/system/inputManager.h"
#include "../../include/system/gameFactory.h"

#include "../../include/audio/audioManager.h"
#include "../../include/audio/knownTracks.h"

#include "../../include/events/eventManager.h"
#include "../../include/events/knownEvents.h"

/// @brief Create a new grid.
/// @param size The size of the grid.
Grid::Grid(int size)
{
    tileX = 0;
    tileY = 0;

    // Setup the grid with the relevant size
    switch (size)
    {
        case 0:
            Setup3x3();
            break;

        case 1:
            Setup4x4();
            break;

        case 2:
        default:
            Setup5x5();
            break;
    }

    // Highlight the top left tile
    tiles[tileX][tileY]->Highlight();
}

/// @brief Destroy the grid.
Grid::~Grid()
{
    // Remove all the header tiles
    for (int i = 0; i<(int)headers.size(); i++)
    {
        delete headers.at(i);
    }

    headers.clear();

    // Remove all the connectors
    for (int i = 0; i < (int)connectors.size(); i++)
    {
        delete connectors.at(i);
    }

    connectors.clear();

    // Remove all the grid tiles
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (tiles[i][j] != nullptr)
            {
                delete tiles[i][j];
            }
        }
    }
}

/// @brief Reset the grid.
/// @param level The current level.
void Grid::Reset(int level)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            tiles[i][j]->Reset();
        }
    }

    GenerateGridValues(level);

    tileX = 0;
    tileY = 0;

    tiles[tileX][tileY]->Highlight();
}

/// @brief Get the currently selected tile.
/// @return The currently selected tile.
GridTile* Grid::GetCurrentTile()
{
    return tiles[tileX][tileY];
}

/// @brief Flip all tiles.
void Grid::FlipAll()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (tiles[i][j]->IsFlipped() == false)
            {
                // Flip the tile without playing sounds
                tiles[i][j]->Flip(false);
            }
        }
    }
}

/// @brief Update the grid.
void Grid::Update()
{
    // Update the currently selected tile
    tiles[tileX][tileY]->Update();

    // Handle movement input
    HandleMovement();

    // Handle tile flips
    HandleFlip();
}

/// @brief Update the grid, but only allow marking.
void Grid::UpdateInMarkerMode()
{
    HandleTouchInput(true);
}

/// @brief Draw the grid.
void Grid::Draw()
{
    // Draw all the headeres
    for (int i = 0; i < (int)headers.size(); i++)
    {
        headers.at(i)->Draw();
    }

    // Draw all the connectors
    for (int i = 0; i < (int)connectors.size(); i++)
    {
        connectors.at(i)->Draw();
    }

    // Draw all the grid tiles
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            tiles[i][j]->Draw();
        }
    }
}

/// @brief Setup a 3x3 grid.
void Grid::Setup3x3()
{
    SetupGrid(3, new Vector2(715, 210));
}

/// @brief Setup a 4x4 grid.
void Grid::Setup4x4()
{
    SetupGrid(4, new Vector2(630, 125));
}

/// @brief Setup a 5x5 grid.
void Grid::Setup5x5()
{
    SetupGrid(5, new Vector2(545, 40));
}

/// @brief Setup a grid.
/// @param size The size of the grid.
/// @param position The position where the top-left header tile should be placed.
void Grid::SetupGrid(int size, Vector2* position)
{
    this->size = size;

    PlaceHeaders(position);
    PlaceConnectors(position);
    PlaceTiles(position);

    GenerateGridValues(1);

    delete position;
}

/// @brief Place the header tiles.
/// @param position The position of the grid.
void Grid::PlaceHeaders(Vector2* position)
{
    // Start at the given position
    int x = position->X();
    int y = position->Y();

    // For the size of the grid
    for (int i = 0; i < size; i++)
    {
        // Add a header tile on the top
        headers.push_back(new HeaderTile((GridColours)i, new Vector2(x, y)));

        // Move the position to the left and down 
        x = position->X() - TileOffset - TileWidth;
        y = position->Y() + ((i+1) * (TileOffset + TileHeight));

        // Add a header tile on the side
        headers.push_back(new HeaderTile((GridColours)i, new Vector2(x, y)));

        // Move the position back to the top, but to the right of the last header tile
        x = position->X() + ((i+1) * (TileOffset + TileWidth));
        y = position->Y();
    }
}

/// @brief Place all the connectors on the grid.
/// @param position The position of the grid.
void Grid::PlaceConnectors(Vector2* position)
{
    // Move the starting position to be offset from the given position
    int x = position->X() + ConnectorOffset;
    int y = position->Y() + TileHeight;

    // For the size of the grid
    for (int i = 0; i < size; i++)
    {
        // Add a connector at the starting position
        connectors.push_back(GameFactory::GetSprite(UIFile, GetConnectorSpriteName((GridColours)i, true), new Vector2(x, y)));

        // Continue adding connectors of the same colour vertically
        for (int j = 1; j < size; j++)
        {
            // Move the offset down past the next tile
            y += TileHeight + TileOffset;

            connectors.push_back(GameFactory::GetSprite(UIFile, GetConnectorSpriteName((GridColours)i, true), new Vector2(x, y)));
        }

        // Reset the position to start adding connectors of the same colour horizontally
        x = position->X() - TileOffset;
        y = position->Y() + TileHeight + TileOffset + ConnectorOffset + (i * (TileHeight + TileOffset));

        // For the size of the grid
        for (int j = 0; j < size; j++)
        {
            // Add a connector
            connectors.push_back(GameFactory::GetSprite(UIFile, GetConnectorSpriteName((GridColours)i, false), new Vector2(x, y)));

            // Move right
            x += TileWidth + TileOffset;
        }

        // Reset the position to add more connectors in the next colour
        x = position->X() + ((i + 1) * (TileWidth + TileOffset)) + ConnectorOffset;
        y = position->Y() + TileHeight;
    }
}

/// @brief Place tiles in the grid.
/// @param position The position of the grid.
void Grid::PlaceTiles(Vector2* position)
{
    // The tiles array is always 5x5
    // This will set them all to null pointers so
    // that the ones that aren't used in 3x3 and 4x4
    // have a 'value' to delete when the grid is
    // destroyed
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            tiles[i][j] = nullptr;
        }
    }

    // Move the start position to be below the header row
    int x = position->X();
    int y = position->Y() + TileOffset + TileHeight;

    // For the size of the grid horizontally
    for (int i = 0; i < size; i++)
    {
        // For the size of the grid vertically
        for (int j = 0; j < size; j++)
        {
            // Create a new grid tile
            tiles[i][j] = new GridTile(new Vector2(x, y));

            // Move the offset down
            y += TileOffset + TileHeight;
        }

        // Move the offset right, and reset the y
        x += TileOffset + TileWidth;
        y = position->Y() + TileOffset + TileHeight;
    }
}

/// @brief Handle movement input.
void Grid::HandleMovement()
{
    // Check the inputs from both the arrow buttons and the left stick
    // and then change the selected tile accordingly.
    // The previous tile has the highlight removed, while the new one
    // gets the highlight added.

    if (InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT_STICK_LEFT)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_TileSelect);

        tiles[tileX][tileY]->Highlight(false);
        tileX = tileX == 0 ? size - 1 : tileX - 1;
        tiles[tileX][tileY]->Highlight();
        return;
    }

    if (InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT_STICK_RIGHT)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_RIGHT))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_TileSelect);

        tiles[tileX][tileY]->Highlight(false);
        tileX = tileX == size - 1 ? 0 : tileX + 1;
        tiles[tileX][tileY]->Highlight();
        return;
    }

    if (InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT_STICK_UP)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_UP))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_TileSelect);

        tiles[tileX][tileY]->Highlight(false);
        tileY = tileY == 0 ? size - 1 : tileY - 1;
        tiles[tileX][tileY]->Highlight();
        return;
    }

    if (InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT_STICK_DOWN)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_DOWN))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_TileSelect);

        tiles[tileX][tileY]->Highlight(false);
        tileY = tileY == size - 1 ? 0 : tileY + 1;
        tiles[tileX][tileY]->Highlight();
        return;
    }
}

/// @brief Handle tiles being flipped.
void Grid::HandleFlip()
{
    // If the A button is pressed, then flip the tile
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_EAST))
    {
        tiles[tileX][tileY]->Flip();
        CheckForGridCompletion();
        return;
    }

    HandleTouchInput();
}

/// @brief Handle touch input on the grid.
/// @param markOnly Whether or not tiles can only be marked.
void Grid::HandleTouchInput(bool markOnly)
{
    // Check touch input on each tile, and flip if selected
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // If a tile is touched
            if (tiles[i][j]->IsTouched())
            {
                // Remove highlight from the current tile (even if the same)
                tiles[tileX][tileY]->Highlight(false);
                
                // Update the current selection to match the tile that is touched
                tileX = i;
                tileY = j;

                // Highlight the tile
                tiles[i][j]->Highlight();

                if (markOnly)
                {
                    EventManager::GetInstance()->FireEvent(EVENT_TILECHANGED);
                }
                else
                {
                    // Flip the tile and check if the grid is completed
                    tiles[i][j]->Flip();
                    CheckForGridCompletion();
                }                
                return;
            }
        }
    }
}

/// @brief Check to see if the grid is complete - all x2 and x3 tiles are flipped.
void Grid::CheckForGridCompletion()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // If the tile is not marked as complete then stop checking and
            // leave the method
            if (tiles[i][j]->IsComplete() == false)
            {
                return;
            }
        }
    }

    // If the grid is considered complete, fire the event
    EventManager::GetInstance()->FireEvent(EVENT_GRIDCOMPLETE);
}

/// @brief Generate the values in the grid.
/// @param level The current level.
void Grid::GenerateGridValues(int level)
{
    // Set the minimum number of tiles to have a non-1 value
    // This should be the size of the grid + 1 (so 3x3 = 4, 4x4 = 5, 5x5 = 6)
    int minTiles = size + 1;

    // Set the maximum number of tiles that can have a non-1 value
    // This should be the total tiles in the grid minus the grid's size
    // (so 3x3 = 6, 4x4 = 12, 5x5 = 20)
    int maxTiles = (size * size) - size;

    // Set the number of slots to fill up with non-1 values to a random number between the two ranges
    int freeSlots = rand() % minTiles + maxTiles;

    // Note: This code doesn't do what it is intended to do and sometimes
    // bombs will not be filled when they are supposed to. Maybe I will
    // come back and fix it at some point, but the game is based on chance
    // anyway so players can just take the W.

    double multiplier = 1 + ((level - 1) / 10);

    // Set the number of bombs to fill to be a random number between 
    int bombsToFill = rand() % (int)(size * multiplier);

    int ignoreColumn = -1;
    int ignoreRow = -1;

    switch (level)
    {
        case 1:
            // Force level 1 to always ignore at least 1 random column and row
            // and always contain 2 bombs
            ignoreColumn = rand() % size;
            ignoreRow = rand() % size;
            bombsToFill = 2;
            break;

        case 2:
            // Force level 2 to always ignore at least 1 random column OR row
            // and always contain 2 bombs
            ignoreColumn = rand() % 2 == 1 ? rand() % size : -1;
            ignoreRow = ignoreColumn == -1 ? rand() % size : -1;
            bombsToFill = 2;
            break;

        default:
            break;
    }

    // Get a random number of x2 values to set, by removing the number of bombs from the free slots
    int x2ToFill = rand() % (freeSlots - bombsToFill);

    // Get a random number of x3 values to set, by removing the number slots already taken
    int x3ToFill = rand() % (freeSlots - bombsToFill - x2ToFill);

    PlaceValuesInGrid(Bomb, bombsToFill, ignoreColumn, ignoreRow);
    PlaceValuesInGrid(Two, x2ToFill);
    PlaceValuesInGrid(Three, x3ToFill);

    SetValuesInHeaders();
}

/// @brief Places tile values randomly throughout the grid.
/// @param value The value to set on the tiles.
/// @param amount The number of tiles to set the value on.
/// @param excludeRow The index of the row to ignore.
/// @param excludeColumn The index of the column to ignore.
void Grid::PlaceValuesInGrid(TileValue value, int amount, int excludeRow, int excludeColumn)
{
    for (int i = 0; i < size; i++)
    {
        int numberOnRow = i == size - 1 ? amount :
                            excludeRow == i ? 0 :
                            rand() % amount;

        while (numberOnRow > 0)
        {
            int index = rand() % size;

            if (tiles[index][i]->GetValue() == One
                && excludeColumn != index)
            {
                tiles[index][i]->SetValue(value);
                numberOnRow--;
                amount--;
            }
            else
            {
                for (int j = 0; j < size; j++)
                {
                    if (tiles[j][i]->GetValue() == One
                        && excludeColumn != j)
                    {
                        tiles[j][i]->SetValue(value);
                        numberOnRow--;
                        amount--;
                        break;
                    } 
                }

                numberOnRow = 0;
            }
        }
    }
}

/// @brief Set the total values of the rows / columns into the header tiles.
void Grid::SetValuesInHeaders()
{
    for (int i = 0; i < size; i++)
    {
        int bombsInColumn = 0;
        int valuesInColumn = 0;

        int bombsInRow = 0;
        int valuesInRow = 0;

        for (int j = 0; j < size; j++)
        {
            // By swapping the i and j values round, it is possible to set
            // both the rows and the columns from the same loops

            // Using j,i gets all values in the row
            switch (tiles[j][i]->GetValue())
            {
                case Bomb:
                    bombsInRow++;
                    break;

                case One:
                    valuesInRow += 1;
                    break;

                case Two:
                    valuesInRow += 2;
                    break;

                case Three:
                    valuesInRow += 3;
                    break;
            }

            // Using i,j gets all values in the column
            switch (tiles[i][j]->GetValue())
            {
                case Bomb:
                    bombsInColumn++;
                    break;

                case One:
                    valuesInColumn += 1;
                    break;

                case Two:
                    valuesInColumn += 2;
                    break;

                case Three:
                    valuesInColumn += 3;
                    break;
            }
        }

        // The headers get added two at a time - one along the top, and one to
        // the left. The header on the top will be i*2 (0, 2, 4...) and should
        // display information about columns, so those values get passed in.
        // The header on the left is for the rows, and will always be one more
        // than the column that was just added (1, 3, 5...).
        headers.at(i * 2)->SetValue(valuesInColumn, bombsInColumn);
        headers.at((i * 2) + 1)->SetValue(valuesInRow, bombsInRow);
    }
}

/// @brief Get the name of the connector sprite based on the given colour.
/// @param colour The colour.
/// @param vertical Whether the connector is vertical.
/// @return The name of the connector sprite.
std::string Grid::GetConnectorSpriteName(GridColours colour, bool vertical)
{
    switch (colour)
    {
        case Red:
            return vertical ? "ConnectorVerticalRed" : "ConnectorHorizontalRed";

        case Green:
            return vertical ? "ConnectorVerticalGreen" : "ConnectorHorizontalGreen";

        case Yellow:
            return vertical ? "ConnectorVerticalYellow" : "ConnectorHorizontalYellow";

        case Blue:
            return vertical ? "ConnectorVerticalBlue" : "ConnectorHorizontalBlue";

        case Purple:
        default:
            return vertical ? "ConnectorVerticalPurple" : "ConnectorHorizontalPurple";
    }
}