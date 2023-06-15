#include "../../include/ui/pauseMenu.h"

#include "../../include/system/gameFactory.h"

#include "../../include/events/eventManager.h"
#include "../../include/events/knownEvents.h"
#include "../../include/system/inputManager.h"
#include "../../include/system/core.h"

#include "../../include/audio/audioManager.h"
#include "../../include/audio/knownTracks.h"

#include "../../include/system/sdlLibrary.h"

PauseMenu *PauseMenu::instance{nullptr};

/// @brief Create a pause menu.
/// @param gameManager The game manager.
PauseMenu::PauseMenu(GameManager* gameManager)
{
    instance = this;

    this->gameManager = gameManager;

    showingOptions = false;

    currentOption = 0;

    options =
    {
        new MenuOption(GameFactory::GetLocalisedString("PauseResume"), new Vector2(710, 295), Resume),
        new MenuOption(GameFactory::GetLocalisedString("Options"), new Vector2(710, 465), ShowOptions),
        new MenuOption(GameFactory::GetLocalisedString("PauseQuit"), 60, new Vector2(710, 635), ReturnToMenu)
    };

    options.at(currentOption)->Highlight();

    selectPrompt = new ButtonPrompt(GameFactory::GetLocalisedString("HintSelect"), "ButtonEast", new Vector2(1550, 900));

    optionsMenu = new OptionsMenu();

    overlayBounds = {0, 0, SCREEN_WIDTH_DOCKED, SCREEN_HEIGHT_DOCKED};
}

/// @brief Destroy the pause menu.
PauseMenu::~PauseMenu()
{
    for (int i = 0; i < (int)options.size(); i++)
    {
        delete options.at(i);
    }

    options.clear();

    delete selectPrompt;

    delete optionsMenu;

    instance = nullptr;
}

/// @brief Update the pause menu.
void PauseMenu::Update()
{
    if (showingOptions)
    {
        UpdateOptions();
    }
    else
    {
        UpdatePause();
    }
}

/// @brief Draw the pause menu.
void PauseMenu::Draw()
{
    // Setup the renderer to draw a transparent background
    SDL_SetRenderDrawColor(SDLLibrary::GetInstance()->GetRenderer(), 0, 0, 0, 128);

    SDL_SetRenderDrawBlendMode(SDLLibrary::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);

    // Draw the transparent background
    SDL_RenderFillRect(SDLLibrary::GetInstance()->GetRenderer(), &overlayBounds);

    if (showingOptions)
    {
        optionsMenu->Draw();
    }
    else
    {
        for (int i = 0; i < (int)options.size(); i++)
        {
            options.at(i)->Draw();
        }

        selectPrompt->Draw();
    }
}

/// @brief Update the pause menu
void PauseMenu::UpdatePause()
{
    // If the input is moved up or down, remove the highlight from the currently selected
    // option and highlight the new option

    if (InputManager::GetInstance()->IsInputPressed(BUTTON_UP)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT_STICK_UP))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuMove);

        options.at(currentOption)->Highlight(false);
        currentOption = currentOption == 0 ? (int)options.size() - 1 : currentOption - 1;
        options.at(currentOption)->Highlight();
        return;
    }

    if (InputManager::GetInstance()->IsInputPressed(BUTTON_DOWN)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT_STICK_DOWN))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuMove);

        options.at(currentOption)->Highlight(false);
        currentOption = currentOption == (int)options.size() - 1 ? 0 : currentOption + 1;
        options.at(currentOption)->Highlight();
        return;
    }

    // If A is pressed, select the current option
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_EAST))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuSelect);

        options.at(currentOption)->Select();
        return;
    }

    // If + or B is pressed, resume the game
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_PLUS)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_SOUTH))
    {        
        Resume();
        return;
    }
}

/// @brief Update the options menu.
void PauseMenu::UpdateOptions()
{
    optionsMenu->Update();

    // If the options menu is closed, go back to the pause menu
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_CLOSEOPTIONSMENU))
    {
        showingOptions = false;
    }
}

/// @brief Resume the game.
void PauseMenu::Resume()
{
    AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuBack);

    EventManager::GetInstance()->FireEvent(EVENT_CLOSEPAUSEMENU);
}

/// @brief Show the options menu.
void PauseMenu::ShowOptions()
{
    instance->showingOptions = true;
}

/// @brief Return to the main menu.
void PauseMenu::ReturnToMenu()
{
    instance->gameManager->ChangeScene(Menu);
}