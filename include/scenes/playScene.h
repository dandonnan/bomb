#include "../gameManager.h"
#include "../graphics/sprite.h"
#include "scenes.h"

#include "../game/grid.h"
#include "../game/playState.h"
#include "../game/markerMenu.h"

#include "../ui/buttonPrompt.h"

#include "../ui/pauseMenu.h"
#include "../ui/levelEndScreen.h"
#include "../ui/scoreWindow.h"

#include <vector>

#define MaxLevel    10  // The highest level

// Indexes of the prompts
#define PromptFlip  0
#define PromptMark  1
#define PromptPause 2

#ifndef PlayScene_H
#define PlayScene_H

// The main game scene.
class PlayScene : public Scene
{
    public:
        PlayScene(GameManager* game);
        virtual ~PlayScene();
        void Update();
        void Draw();

    private:
        GameManager *gameManager;

        Sprite *background;

        Grid *grid;

        PlayState state;

        PlayState stateBeforePause;

        MarkerMenu *markerMenu;

        PauseMenu *pauseMenu;
        LevelEndScreen *levelEndScreen;
        ScoreWindow *scoreWindow;

        std::vector<ButtonPrompt*> prompts;

        int level;
        int score;
        int totalScore;

        void UpdateGame();
        void UpdateMarker();
        void UpdatePaused();
        void UpdateGameOver();

        void DrawPrompts();
        void DrawMarker();
        void DrawPaused();
        void DrawGameOver();

        void Reset();
        void MultiplyScore(int amount);
};

#endif // PlayScene_H