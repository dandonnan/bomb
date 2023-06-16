#include "optionsMenu.h"

#include "../gameManager.h"

#include "../ui/menuOption.h"
#include "../ui/buttonPrompt.h"

#include <vector>

#include <SDL.h>

#ifndef PauseMenu_H
#define PauseMenu_H

// The pause menu.
class PauseMenu
{
    public:
        PauseMenu(GameManager* gameManager);
        ~PauseMenu();

        void Update();
        void Draw();

    private:
        static PauseMenu *instance;

        GameManager *gameManager;

        std::vector<MenuOption*> options;

        ButtonPrompt *selectPrompt;

        SDL_Rect overlayBounds;

        int currentOption;

        bool showingOptions;

        OptionsMenu *optionsMenu;

        void UpdatePause();
        void UpdateOptions();

        static void Resume();
        static void ShowOptions();
        static void ReturnToMenu();

        void SelectOption(int index);
};

#endif // PauseMenu_H