#include "../../include/game/markerMenu.h"

#include "../../include/system/inputManager.h"
#include "../../include/system/core.h"

#include "../../include/events/eventManager.h"
#include "../../include/events/knownEvents.h"

#include "../../include/system/gameFactory.h"

#include "../../include/audio/audioManager.h"
#include "../../include/audio/knownTracks.h"

/// @brief Create a new menu for marking a tile.
MarkerMenu::MarkerMenu()
{
    background = GameFactory::GetInstance()->GetSprite(UIFile, "MarkerMenu", new Vector2(1620, 500));

    selector = GameFactory::GetInstance()->GetSprite(UIFile, "MarkerSelector", new Vector2(0, 0));

    tiles[0] = GameFactory::GetInstance()->GetSprite(UIFile, "MarkedBomb", new Vector2(1624, 504));
    tiles[1] = GameFactory::GetInstance()->GetSprite(UIFile, "MarkedOne", new Vector2(1726, 504));
    tiles[2] = GameFactory::GetInstance()->GetSprite(UIFile, "MarkedTwo", new Vector2(1624, 606));
    tiles[3] = GameFactory::GetInstance()->GetSprite(UIFile, "MarkedThree", new Vector2(1726, 606));

    markerHighlight = GameFactory::GetInstance()->GetSprite(UIFile, "MarkedTile", new Vector2(0, 0));

    selectedTile = 0;

    selectorPosition = nullptr;

    selectorPosition = GetSelectorPosition();
}

/// @brief Destroy the marking menu.
MarkerMenu::~MarkerMenu()
{
    delete background;

    delete selector;

    delete markerHighlight;

    delete selectorPosition;

    for (int i = 0; i < TotalMarkings; i++)
    {
        delete tiles[i];
    }
}

/// @brief Set the grid tile to mark.
/// @param gridTile The tile to mark.
void MarkerMenu::SetTile(GridTile* gridTile)
{
    this->gridTile = gridTile;

    // Set the position of the highlight to the tile's position
    markerHighlight->SetPosition(gridTile->GetPosition());
}

/// @brief Update the menu.
void MarkerMenu::Update()
{
    // Update the tile that is being marked to handle it's own input
    gridTile->Update();

    // If movement input is pressed, then change the selected marker tile
    // and update the position of the selector sprite
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT_STICK_LEFT)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_RIGHT)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT_STICK_RIGHT))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuMove);

        selectedTile = selectedTile == 0 || selectedTile == 2 ? selectedTile + 1 : selectedTile - 1;
        selectorPosition = GetSelectorPosition();
        return;
    }

    if (InputManager::GetInstance()->IsInputPressed(BUTTON_UP)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT_STICK_UP)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_DOWN)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT_STICK_DOWN))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuMove);

        selectedTile = selectedTile == 0 || selectedTile == 1 ? selectedTile + 2 : selectedTile - 2;
        selectorPosition = GetSelectorPosition();
        return;
    }

    // If the B button is pressed, close the menu
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_SOUTH))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuBack);

        EventManager::GetInstance()->FireEvent(EVENT_CLOSEMARKERMENU);
        return;
    }

    // If the A button is pressed, toggle the marking on the grid tile
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_EAST))
    {
        gridTile->ToggleMark((TileValue)selectedTile);
        return;
    }
}

/// @brief Draw the marker menu.
void MarkerMenu::Draw()
{
    markerHighlight->Draw();

    background->Draw();

    selector->Draw(selectorPosition);

    for (int i = 0; i < TotalMarkings; i++)
    {
        // If the grid tile has any markings, then draw a
        // highlighted version of that marking on the menu
        if (gridTile->IsMarked(i))
        {
            tiles[i]->Draw();
        }
    }
}

/// @brief Get the position of the selector sprite.
/// @return The position.
Vector2* MarkerMenu::GetSelectorPosition()
{
    Vector2 *newPosition;

    Vector2* oldPosition = selectorPosition;

    switch (selectedTile)
    {
        case 0:
        default:
            newPosition = new Vector2(1622, 502);
            break;

        case 1:
            newPosition = new Vector2(1724, 502);
            break;

        case 2:
            newPosition = new Vector2(1622, 604);
            break;

        case 3:
            newPosition = new Vector2(1724, 604);
            break;
    }

    delete oldPosition;

    return newPosition;
}