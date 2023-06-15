#include "../../include/gameManager.h"

#include "../../include/events/eventManager.h"
#include "../../include/audio/audioManager.h"
#include "../../include/audio/knownTracks.h"

#include "../../include/scenes/titleScene.h"
#include "../../include/scenes/menuScene.h"
#include "../../include/scenes/playScene.h"

/// @brief Create a game manager.
/// @param version The game version.
GameManager::GameManager(std::string version)
{
    this->version = version;

    scene = new TitleScene(this, version);

    AudioManager::GetInstance()->PlayMusic(Music_Background);

    gridSize = 0;
}

/// @brief Destroy the game manager.
GameManager::~GameManager()
{
    delete scene;
}

/// @brief Set the size of the grid.
/// @param size The size of the grid.
void GameManager::SetGridSize(int size)
{
    gridSize = size;
}

/// @brief Get the size of the grid.
/// @return The size of the grid.
int GameManager::GetGridSize()
{
    return gridSize;
}

/// @brief Change the scene.
/// @param nextScene The new scene.
void GameManager::ChangeScene(Scenes nextScene)
{
    // Get the current scene
    Scene* currentScene = scene;

    switch (nextScene)
    {
        case Title:
            scene = new TitleScene(this, version);
            break;

        case Menu:
            scene = new MenuScene(this);
            break;

        case Play:
            scene = new PlayScene(this);
            break;
    }

    // Unload the current scene
    delete currentScene;
}

/// @brief Update the game.
void GameManager::Update()
{
    EventManager::GetInstance()->Update();

    scene->Update();
}

/// @brief Draw the game.
void GameManager::Draw()
{
    scene->Draw();
}