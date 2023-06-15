#include "../../include/ui/optionsMenu.h"

#include "../../include/system/inputManager.h"
#include "../../include/events/eventManager.h"
#include "../../include/events/knownEvents.h"
#include "../../include/system/saveManager.h"
#include "../../include/system/gameFactory.h"

#include "../../include/audio/audioManager.h"
#include "../../include/audio/knownTracks.h"

/// @brief Create the options menu.
OptionsMenu::OptionsMenu()
{
    currentOption = 0;

    options =
    {
        new MenuOption(GameFactory::GetLocalisedString("OptionSound"), new Vector2(710, 295), UpdateSound),
        new MenuOption(GameFactory::GetLocalisedString("OptionMusic"), new Vector2(710, 465), UpdateMusic)
    };

    on = GameFactory::GetLocalisedString("OptionOn");
    off = GameFactory::GetLocalisedString("OptionOff");

    values =
    {
        GameFactory::GetText(SaveManager::GetInstance()->Data()->SoundOn() ? on : off, 30, new Vector2(1140, 355)),
        GameFactory::GetText(SaveManager::GetInstance()->Data()->MusicOn() ? on : off, 30, new Vector2(1140, 525))
    };

    prompts =
    {
        new ButtonPrompt(GameFactory::GetLocalisedString("HintBack"), "ButtonSouth", new Vector2(50, 900)),
        new ButtonPrompt(GameFactory::GetLocalisedString("HintToggle"), "ButtonEast", new Vector2(1550, 900))
    };

    options.at(currentOption)->Highlight();
}

/// @brief Destroy the options menu.
OptionsMenu::~OptionsMenu()
{
    for (int i = 0; i < (int)options.size(); i++)
    {
        delete options.at(i);
        delete values.at(i);
    }

    options.clear();
    values.clear();

    for (int i = 0; i < (int)prompts.size(); i++)
    {
        delete prompts.at(i);
    }

    options.clear();
}

/// @brief Update the options menu.
void OptionsMenu::Update()
{
    // If sound has been toggled then update the value
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_SOUNDTOGGLED))
    {
        values.at(0)->UpdateText(SaveManager::GetInstance()->Data()->SoundOn() ? on : off);
    }

    // If music has been toggled then update the value
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_MUSICTOGGLED))
    {
        values.at(1)->UpdateText(SaveManager::GetInstance()->Data()->MusicOn() ? on : off);
    }

    // If + or B is pressed, close the options menu
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_PLUS)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_SOUTH))
    {
        Close();
        return;
    }

    // If up or down is pressed, remove the highlight from the current option and
    // highlight the newly selected option

    if (InputManager::GetInstance()->IsInputPressed(BUTTON_UP)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT_STICK_UP))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuMove);

        options[currentOption]->Highlight(false);
        currentOption = currentOption == 0 ? (int)options.size() - 1 : currentOption - 1;
        options[currentOption]->Highlight();
        return;
    }

    if (InputManager::GetInstance()->IsInputPressed(BUTTON_DOWN)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_LEFT_STICK_DOWN))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuMove);

        options[currentOption]->Highlight(false);
        currentOption = currentOption == (int)options.size() - 1 ? 0 : currentOption + 1;
        options[currentOption]->Highlight();
        return;
    }

    // If A is pressed, select the option
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_EAST))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuSelect);

        options.at(currentOption)->Select();
        return;
    }
}

/// @brief Draw the options menu.
void OptionsMenu::Draw()
{
    for (int i = 0; i < (int)options.size(); i++)
    {
        options.at(i)->Draw();
        values.at(i)->Draw();
    }

    for (int i = 0; i < (int)prompts.size(); i++)
    {
        prompts.at(i)->Draw();
    }
}

/// @brief Close the options menu.
void OptionsMenu::Close()
{
    SaveManager::GetInstance()->Save();

    AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuBack);

    EventManager::GetInstance()->FireEvent(EVENT_CLOSEOPTIONSMENU);
}

/// @brief Update the music value.
void OptionsMenu::UpdateMusic()
{
    AudioManager::GetInstance()->PlaySoundEffect("MenuMove");

    SaveManager::GetInstance()->Data()->ToggleMusic();

    // Start or stop the music depending on the new value
    if (SaveManager::GetInstance()->Data()->MusicOn())
    {
        AudioManager::GetInstance()->PlayMusic(Music_Background);
    }
    else
    {
        AudioManager::GetInstance()->StopMusic();
    }

    EventManager::GetInstance()->FireEvent(EVENT_MUSICTOGGLED);
}

/// @brief Update the sound effect value.
void OptionsMenu::UpdateSound()
{
    SaveManager::GetInstance()->Data()->ToggleSound();

    AudioManager::GetInstance()->PlaySoundEffect("MenuMove");

    EventManager::GetInstance()->FireEvent(EVENT_SOUNDTOGGLED);
}