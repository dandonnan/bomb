#include "../../include/scenes/playScene.h"

#include "../../include/events/eventManager.h"
#include "../../include/events/knownEvents.h"

#include "../../include/system/inputManager.h"

#include "../../include/audio/audioManager.h"
#include "../../include/audio/knownTracks.h"

/// @brief Create the main game screen.
/// @param game The game manager.
PlayScene::PlayScene(GameManager* game)
{
    gameManager = game;

    background = GameFactory::GetSprite("data/images/background.png", new Vector2(0, 0));

    prompts =
    {
        new ButtonPrompt(GameFactory::GetLocalisedString("HintFlip"), "ButtonEast", new Vector2(1550, 900)),
        new ButtonPrompt(GameFactory::GetLocalisedString("HintMarker"), "ButtonSouth", new Vector2(1550, 750)),
        new ButtonPrompt(GameFactory::GetLocalisedString("Pause"), "ButtonPlus", new Vector2(1550, 50))
    };

    markerMenu = new MarkerMenu();

    grid = new Grid(gameManager->GetGridSize());

    state = Playing;

    pauseMenu = new PauseMenu(gameManager);
    levelEndScreen = new LevelEndScreen();
    scoreWindow = new ScoreWindow();

    level = 1;
    score = 0;
    totalScore = 0;
}

/// @brief Destroy the main game scene.
PlayScene::~PlayScene()
{
    delete background;

    for (int i = 0; i < (int)prompts.size(); i++)
    {
        delete prompts.at(i);
    }

    prompts.clear();

    delete markerMenu;

    delete grid;

    delete pauseMenu;

    delete levelEndScreen;

    delete scoreWindow;
}

/// @brief Update the scene.
void PlayScene::Update()
{
    switch (state)
    {
        case Playing:
            UpdateGame();
            break;

        case Marking:
            UpdateMarker();
            break;

        case Paused:
            UpdatePaused();
            break;

        case GameOver:
            UpdateGameOver();
            break;
    }
}

/// @brief Draw the scene.
void PlayScene::Draw()
{
    background->Draw();

    grid->Draw();

    scoreWindow->Draw();

    switch (state)
    {
        case Playing:
            DrawPrompts();
            break;

        case Marking:
            DrawMarker();
            break;

        case Paused:
            DrawPaused();
            break;

        case GameOver:
            DrawGameOver();
            break;
    }
}

/// @brief Update the main game.
void PlayScene::UpdateGame()
{
    // Update the grid
    grid->Update();

    // If B is pressed and the selected tile has not been flipped, or the
    // marker prompt has been touched, open up the marking menu
    if ((InputManager::GetInstance()->IsInputPressed(BUTTON_SOUTH)
        && grid->GetCurrentTile()->IsFlipped() == false)
        || prompts.at(PromptMark)->IsTouched())
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuBack);

        markerMenu->SetTile(grid->GetCurrentTile());
        state = Marking;
        return;
    }

    // If the flip prompt is pressed, flip the currently selected tile
    if (prompts.at(PromptFlip)->IsTouched())
    {
        grid->GetCurrentTile()->Flip();
    }

    // If + is pressed, or the prompt is touched, pause the game
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_PLUS)
        || prompts.at(PromptPause)->IsTouched())
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuBack);

        stateBeforePause = Playing;
        state = Paused;
        return;
    }

    // If a x1 tile has been flipped, either increase the score or leave it as it is
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_MULTIPLYBY1))
    {
        MultiplyScore(1);
    }
    
    // If a x2 tile has been flipped, multiply the score
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_MULTIPLYBY2))
    {
        MultiplyScore(2);
    }

    // If a x3 tile has been flipped, multiply the score
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_MULTIPLYBY3))
    {
        MultiplyScore(3);
    }

    // If the grid has been completed, show the game over screen with the win condition
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_GRIDCOMPLETE))
    {
        grid->FlipAll();
        AudioManager::GetInstance()->PlaySoundEffect(Sound_GridComplete);
        levelEndScreen->Show(true);
        state = GameOver;
        return;
    }

    // If a bomb has been flipped, show the game over screen with the lose condition
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_GAMEOVER))
    {
        grid->FlipAll();
        levelEndScreen->Show(false);
        state = GameOver;
        return;
    }
}

/// @brief Update the game in the marker state.
void PlayScene::UpdateMarker()
{
    // Update the grid
    grid->UpdateInMarkerMode();

    // Update the marker menu
    markerMenu->Update();

    // If + is pressed, pause the game
    if (InputManager::GetInstance()->IsInputPressed(BUTTON_PLUS))
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuBack);

        stateBeforePause = Marking;
        state = Paused;
        return;
    }

    // If the marker menu has been closed, return to the game
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_CLOSEMARKERMENU)
        || prompts.at(PromptMark)->IsTouched())
    {
        AudioManager::GetInstance()->PlaySoundEffect(Sound_MenuBack);

        state = Playing;
        return;
    }

    // If the selected tile has changed, update the tile used in the marker menu
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_TILECHANGED))
    {
        markerMenu->SetTile(grid->GetCurrentTile());
    }
}

/// @brief Update the game in the pause state.
void PlayScene::UpdatePaused()
{
    // Update the pause menu
    pauseMenu->Update();

    // If the pause menu is closed, resume the game
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_CLOSEPAUSEMENU))
    {
        state = stateBeforePause;
    }
}

/// @brief Update the game in the game over state.
void PlayScene::UpdateGameOver()
{
    // Update the level end screen
    levelEndScreen->Update();

    // If the restart event is triggered, restart the game
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_RESTART))
    {
        level = level > 1 ? level - 1 : 1;
        Reset();
        return;
    }

    // If the move to the next level event is triggered, restart the game
    if (EventManager::GetInstance()->HasEventFiredThenKill(EVENT_NEXTLEVEL))
    {
        level = level < MaxLevel ? level + 1 : MaxLevel;
        Reset();
        return;
    }
}

/// @brief Draw button prompts.
void PlayScene::DrawPrompts()
{
    for (int i = 0; i < (int)prompts.size(); i++)
    {
        prompts.at(i)->Draw();
    }
}

/// @brief Draw the game in the marker state.
void PlayScene::DrawMarker()
{
    DrawPrompts();
    markerMenu->Draw();
}

/// @brief Draw the game in the pause state.
void PlayScene::DrawPaused()
{
    pauseMenu->Draw();
}

/// @brief Draw the game in the game over state.
void PlayScene::DrawGameOver()
{
    levelEndScreen->Draw();
}

/// @brief Resets the level
void PlayScene::Reset()
{
    grid->Reset(level);
    totalScore += score;
    score = 0;
    scoreWindow->SetLevel(level);
    scoreWindow->UpdateScore(score, totalScore);
    state = Playing;
}

/// @brief Multiply the score by the amount.
/// @param amount The amount to multiply by.
void PlayScene::MultiplyScore(int amount)
{
    score = score == 0 ? amount : score * amount;
    scoreWindow->UpdateScore(score, totalScore + score);
}