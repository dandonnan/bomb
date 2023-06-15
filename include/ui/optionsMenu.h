#include "menuOption.h"

#include "../graphics/displayText.h"
#include "../ui/buttonPrompt.h"

#include <vector>

#ifndef OptionsMenu_H
#define OptionsMenu_H

// The options menu.
class OptionsMenu{
    public:
        OptionsMenu();
        ~OptionsMenu();

        void Update();
        void Draw();

    private:
        std::vector<MenuOption*> options;

        std::vector<DisplayText*> values;

        std::string on;
        std::string off;

        std::vector<ButtonPrompt*> prompts;

        int currentOption;

        static void Close();

        static void UpdateMusic();
        static void UpdateSound();
};

#endif // OptionsMenu_H