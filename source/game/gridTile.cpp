#include "../../include/game/gridTile.h"

#include "../../include/system/gameFactory.h"
#include "../../include/events/eventManager.h"
#include "../../include/events/knownEvents.h"

#include "../../include/system/inputManager.h"
#include "../../include/system/core.h"

#include "../../include/audio/audioManager.h"
#include "../../include/audio/knownTracks.h"

/// @brief Create a new tile in the grid.
/// @param position The tile's position.
GridTile::GridTile(Vector2* position)
{
    background = GameFactory::GetSprite(UIFile, "UnflippedTile", position);
    highlight = GameFactory::GetSprite(UIFile, "HighlightedTile", position);

    this->position = new Vector2(position->X(), position->Y());

    SetValue(One);
    state = NotFlipped;

    isHighlighted = false;

    SetupMarkings();

    ResetMarkings();

    delete position;
}

/// @brief Destroy the grid tile.
GridTile::~GridTile()
{
    delete background;
    delete highlight;

    delete position;

    delete valueIcon;
}

/// @brief Get the position of the tile.
/// @return The tile's position.
Vector2* GridTile::GetPosition()
{
    return position;
}

/// @brief Get whether the tile is flipped.
/// @return true if flipped. false if not.
bool GridTile::IsFlipped()
{
    return state == Flipped;
}

/// @brief Get whether the tile has a specific marking.
/// @param marking The index of the marking to check.
/// @return true if the tile has the specified marking. false if not.
bool GridTile::IsMarked(int marking)
{
    return markings[marking];
}

/// @brief Get whether the tile is considered complete.
///        Tiles with values of 1 or a Bomb are always considered
///        complete, but values with 2 or 3 are only complete if
///        they have been flipped.
/// @return true if complete. false if not.
bool GridTile::IsComplete()
{
    if (value == Bomb || value == One)
    {
        return true;
    }

    return state == Flipped;
}

/// @brief Toggle a marking on the tile.
/// @param value The marking to toggle.
void GridTile::ToggleMark(TileValue value)
{
    // Only toggle the marking if the tile has not been flipped
    if (state == NotFlipped)
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_TileSelect);
        
        markings[(int)value] = !markings[(int)value];
    }
}

/// @brief Set the value on the tile.
/// @param value The value.
void GridTile::SetValue(TileValue value)
{
    this->value = value;

    // Set an offset for the image of the value
    Vector2 *position = new Vector2(background->GetPosition()->X() + 8, background->GetPosition()->Y() + 8);

    switch (value)
    {
        case One:
        default:
            valueIcon = GameFactory::GetSprite(UIFile, "TileOne", position);
            break;

        case Two:
            valueIcon = GameFactory::GetSprite(UIFile, "TileTwo", position);
            break;

        case Three:
            valueIcon = GameFactory::GetSprite(UIFile, "TileThree", position);
            break;

        case Bomb:
            valueIcon = GameFactory::GetSprite(UIFile, "TileBomb", position);
            break;
    }
}

/// @brief Get the tile's value.
/// @return The tile's value.
TileValue GridTile::GetValue()
{
    return value;
}

/// @brief Highlight the tile.
///        If no value is passed, this defaults to true.
/// @param highlight Whether or not to highlight the tile.
void GridTile::Highlight(bool highlight)
{
    isHighlighted = highlight;
}

/// @brief Reset the tile to the default state.
void GridTile::Reset()
{
    state = NotFlipped;

    isHighlighted = false;

    SetValue(One);

    ResetMarkings();
    ResetBackground("UnflippedTile");
}

/// @brief Flip the tile.
/// @param withSound Whether or not to play sound effects
void GridTile::Flip(bool withSound)
{
    if (state == NotFlipped)
    {
        state = Flipped;

        ResetBackground("FlippedTile");

        // If a sound should be played, play the right one depending on what was flipped
        if (withSound)
        {
            AudioManager::GetInstance()->PlaySoundEffect(value == Bomb ? Sound_Explosion : Sound_TileFlip);
        }

        // Trigger events based on the value
        switch (value)
        {
            case One:
                EventManager::GetInstance()->FireEvent(EVENT_MULTIPLYBY1);
                break;

            case Two:
                EventManager::GetInstance()->FireEvent(EVENT_MULTIPLYBY2);
                break;

            case Three:
                EventManager::GetInstance()->FireEvent(EVENT_MULTIPLYBY3);
                break;

            case Bomb:
                EventManager::GetInstance()->FireEvent(EVENT_GAMEOVER);
                break;

            default:
                break;
        }
    }
}

/// @brief Get whether the tile is touched.
/// @return true if touched. false if not.
bool GridTile::IsTouched()
{
    return background->IsTouched();
}

/// @brief Update the tile.
void GridTile::Update()
{
    HandleMarking();
}

/// @brief Draw the tile.
void GridTile::Draw()
{
    background->Draw();
    
    // Draw a highlight if highlighted
    if (isHighlighted)
    {
        highlight->Draw();
    }

    if (state == Flipped)
    {
        // Draw the value if flipped
        valueIcon->Draw();
    }
    else
    {
        // Draw any markings if the tile is marked
        for (int i = 0; i < TotalMarkings; i++)
        {
            if (markings[i])
            {
                markerIcons[i]->Draw();
            }
        }
    }
}

/// @brief Reset the background the tile uses.
/// @param newBackground The new background to use.
void GridTile::ResetBackground(std::string newBackground)
{
    // Get the old background so that the pointer for it can be deleted
    Sprite* oldBackground = background;

    background = GameFactory::GetSprite(UIFile, newBackground, oldBackground->GetPosition());

    delete oldBackground;
}

/// @brief Setup the marking images.
void GridTile::SetupMarkings()
{
    Vector2 *position = background->GetPosition();

    int offsetLeft = 8;
    int offsetRight = 110;

    markerIcons[0] = GameFactory::GetSprite(UIFile, "MarkerBomb", new Vector2(position->X() + offsetLeft, position->Y() + offsetLeft));
    markerIcons[1] = GameFactory::GetSprite(UIFile, "MarkerOne", new Vector2(position->X() + offsetRight, position->Y() + offsetLeft));
    markerIcons[2] = GameFactory::GetSprite(UIFile, "MarkerTwo", new Vector2(position->X() + offsetLeft, position->Y() + offsetRight));
    markerIcons[3] = GameFactory::GetSprite(UIFile, "MarkerThree", new Vector2(position->X() + offsetRight, position->Y() + offsetRight));
}

/// @brief Reset the markings on the tile.
void GridTile::ResetMarkings()
{
    for (int i = 0; i < TotalMarkings; i++)
    {
        markings[i] = false;
    }
}

/// @brief Handle the input for marking the tile.
void GridTile::HandleMarking()
{
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_L))
    {
        ToggleMark(Bomb);
    }

    if (InputManager::GetInstance()->IsInputPressed(BUTTON_ZL))
    {
        ToggleMark(Two);
    }

    if (InputManager::GetInstance()->IsInputPressed(BUTTON_R))
    {
        ToggleMark(One);
    }

    if (InputManager::GetInstance()->IsInputPressed(BUTTON_ZR))
    {
        ToggleMark(Three);
    }
}