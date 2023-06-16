#include "../../include/ui/levelEndScreen.h"

#include "../../include/system/inputManager.h"
#include "../../include/system/core.h"

#include "../../include/events/eventManager.h"
#include "../../include/events/knownEvents.h"

#include "../../include/system/gameFactory.h"

#include "../../include/audio/audioManager.h"
#include "../../include/audio/knownTracks.h"

/// @brief Create the level end screen.
LevelEndScreen::LevelEndScreen()
{
    moveUp = false;

    state = Reveal;

    textBox = new TextBox(".", new Vector2(460, 950));
}

/// @brief Destroy the level end screen.
LevelEndScreen::~LevelEndScreen()
{
    delete textBox;
}

/// @brief Show the level end screen.
/// @param levelComplete Whether the level was completed or not.
void LevelEndScreen::Show(bool levelComplete)
{
    if (levelComplete == false)
    {
        AudioManager::GetInstance()->StopMusic();
    }

    textBox->UpdateText(levelComplete ? GameFactory::GetLocalisedString("GameOverSuccess") : GameFactory::GetLocalisedString("GameOverOhNo"));

    moveUp = levelComplete;
    state = Reveal;
}

/// @brief Update the level end screen
void LevelEndScreen::Update()
{
    switch (state)
    {
        case Reveal:
            UpdateReveal();
            break;

        case Message:
            UpdateMessage();
            break;

        case Reset:
            UpdateReset();
            break;
    }
}

/// @brief Draw the level end screen
void LevelEndScreen::Draw()
{
    switch (state)
    {
        case Reveal:
            break;

        case Message:
        case Reset:
            DrawDialogue();
            break;
    }
}

/// @brief Update when revealing all tiles on the grid.
void LevelEndScreen::UpdateReveal()
{
    state = Message;
}

/// @brief Update when displaying the message.
void LevelEndScreen::UpdateMessage()
{
    // If A is pressed or the touch screen is touched
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_EAST)
        || InputManager::GetInstance()->IsTouched())
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuSelect);

        textBox->UpdateText(GameFactory::GetLocalisedString("GameOverReset"));

        state = Reset;
    }
}

/// @brief Update before resetting the grid.
void LevelEndScreen::UpdateReset()
{
    // If A is pressed or the touch screen is touched
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_EAST)
        || InputManager::GetInstance()->IsTouched())
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuSelect);        

        // If the level was completed, move to the next level
        if (moveUp)
        {
            EventManager::GetInstance()->FireEvent(EVENT_NEXTLEVEL);
        }
        // Otherwise restart
        else
        {
            AudioManager::GetInstance()->PlayMusic(Music_Background);
            EventManager::GetInstance()->FireEvent(EVENT_RESTART);
        }
    }
}

/// @brief Draw the dialogue box.
void LevelEndScreen::DrawDialogue()
{
    textBox->Draw();
}