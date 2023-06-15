#include "../gameManager.h"
#include "../graphics/sprite.h"
#include "scenes.h"

#include "../ui/menuOption.h"
#include "../ui/optionsMenu.h"
#include "../ui/buttonPrompt.h"

#include <vector>

#ifndef MenuScene_H
#define MenuScene_H

// The main menu screen.
class MenuScene : public Scene
{
    public:
        MenuScene(GameManager* game);
        virtual ~MenuScene();
        void Update();
        void Draw();

    private:
        static MenuScene *instance;

        Sprite *background;
        GameManager *gameManager;

        ButtonPrompt *selectPrompt;

        std::vector<MenuOption*> options;

        int currentOption;

        OptionsMenu *optionsMenu;

        bool showingOptions;

        void UpdateMenu();
        void UpdateOptions();

        void DrawMenu();
        void DrawOptions();

        static void Play3x3();
        static void Play4x4();
        static void Play5x5();

        static void ShowOptions();
};

#endif // MenuScene_H