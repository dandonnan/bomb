#include "../../include/scenes/menuScene.h"

#include "../../include/system/gameFactory.h"

#include "../../include/events/eventManager.h"
#include "../../include/events/knownEvents.h"

#include "../../include/system/inputManager.h"

#include "../../include/audio/audioManager.h"
#include "../../include/audio/knownTracks.h"

MenuScene *MenuScene::instance{nullptr};

/// @brief Create the main menu.
/// @param game The game manager.
MenuScene::MenuScene(GameManager* game)
{
    instance = this;

    gameManager = game;

    background = GameFactory::GetSprite("data/images/background.png", new Vector2(0, 0));

    // Setup the options
    options =
    {
        new MenuOption(GameFactory::GetLocalisedString("Grid3x3"), new Vector2(710, 210), Play3x3),
        new MenuOption(GameFactory::GetLocalisedString("Grid4x4"), new Vector2(710, 380), Play4x4),
        new MenuOption(GameFactory::GetLocalisedString("Grid5x5"), new Vector2(710, 550), Play5x5),
        new MenuOption(GameFactory::GetLocalisedString("Options"), new Vector2(710, 720), ShowOptions)
    };

    currentOption = 0;

    options.at(0)->Highlight();

    showingOptions = false;

    selectPrompt = new ButtonPrompt(GameFactory::GetLocalisedString("HintSelect"), "ButtonEast", new Vector2(1550, 900));

    optionsMenu = new OptionsMenu();
}

/// @brief Destroy the menu.
MenuScene::~MenuScene()
{
    delete background;

    for (int i = 0; i < (int)options.size(); i++)
    {
        delete options.at(i);
    }

    options.clear();

    delete selectPrompt;

    delete optionsMenu;

    instance = nullptr;
}

/// @brief Update the menu.
void MenuScene::Update()
{
    if (showingOptions)
    {
        UpdateOptions();
    }
    else
    {
        UpdateMenu();
    }
}

/// @brief Draw the menu.
void MenuScene::Draw()
{
    background->Draw();

    if (showingOptions)
    {
        DrawOptions();
    }
    else
    {
        DrawMenu();
    }
}

/// @brief Update the main menu.
void MenuScene::UpdateMenu()
{
    // Check the movement input and change the currently selected option by removing
    // the highlight from the old option and highlighting the new one.
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

    // If A is pressed, select the option
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_EAST)
        || selectPrompt->IsTouched())
    {
        SelectOption(currentOption);
        return;
    }

    // Cycle through options to see if they have been touched
    for (int i = 0; i < (int)options.size(); i++)
    {
        if (options.at(i)->IsTouched())
        {
            SelectOption(i);
            return;
        }
    }
}

/// @brief Update the options menu.
void MenuScene::UpdateOptions()
{
    optionsMenu->Update();

    // If the options menu is closed, go back to the main menu
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_CLOSEOPTIONSMENU))
    {
        showingOptions = false;
    }
}

/// @brief Draw the main menu.
void MenuScene::DrawMenu()
{
    for (int i = 0; i < (int)options.size(); i++)
    {
        options.at(i)->Draw();
    }

    selectPrompt->Draw();
}

/// @brief Draw the options menu.
void MenuScene::DrawOptions()
{
    optionsMenu->Draw();
}

/// @brief Start the game with a 3x3 grid.
void MenuScene::Play3x3()
{
    AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuSelect);

    instance->gameManager->SetGridSize(0);
    instance->gameManager->ChangeScene(Play);
}

/// @brief Start the game with a 4x4 grid.
void MenuScene::Play4x4()
{
    AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuSelect);

    instance->gameManager->SetGridSize(1);
    instance->gameManager->ChangeScene(Play);
}

/// @brief Start the game with a 5x5 grid.
void MenuScene::Play5x5()
{
    AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuSelect);

    instance->gameManager->SetGridSize(2);
    instance->gameManager->ChangeScene(Play);
}

/// @brief Show the options menu.
void MenuScene::ShowOptions()
{
    instance->showingOptions = true;
}

/// @brief Select the option at the given index.
/// @param index The index.
void MenuScene::SelectOption(int index)
{
    AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuSelect);

    options.at(index)->Select();
}