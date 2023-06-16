#include "../../include/scenes/titleScene.h"

#include "../../include/system/core.h"
#include "../../include/system/inputManager.h"
#include "../../include/system/gameFactory.h"

#include "../../include/audio/audioManager.h"
#include "../../include/audio/knownTracks.h"

/// @brief Create the title screen.
/// @param game The game manager.
/// @param version The game's version.
TitleScene::TitleScene(GameManager* game, std::string version)
{
    gameManager = game;

    logo = GameFactory::GetSprite("data/images/logo.png", new Vector2(570, 50));

    background = GameFactory::GetSprite("data/images/background.png", new Vector2(0, 0));

    strings =
    {
        GameFactory::GetText(GameFactory::GetLocalisedString("PressStart"), 100, new Vector2(800, 800)),
        GameFactory::GetText("v" + version, 30, new Vector2(10, 1020)),
        GameFactory::GetText(GameFactory::GetLocalisedString("DevelopedBy"), 30, new Vector2(1550, 1020))
    };
}

/// @brief Destroy the title screen.
TitleScene::~TitleScene()
{
    delete logo;

    delete background;

    for (int i = 0; i < (int)strings.size(); i++)
    {
        delete strings.at(i);
    }

    strings.clear();
}

/// @brief Update the scene.
void TitleScene::Update()
{
    // If + or A are pressed, go to the main menu
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_PLUS)
        || InputManager::GetInstance()->IsInputPressed(BUTTON_EAST)
        || InputManager::GetInstance()->IsTouched())
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuSelect);
        gameManager->ChangeScene(Menu);
    }
}

/// @brief Draw the scene.
void TitleScene::Draw()
{
    background->Draw();

    logo->Draw();

    for (int i = 0; i < (int)strings.size(); i++)
    {
        strings.at(i)->Draw();
    }
}
