#include "../ui/textBox.h"

#include "../game/levelEndState.h"

#ifndef LevelEndScreen_H
#define LevelEndScreen_H

// The screen that displays when a level is over.
class LevelEndScreen
{
    public:
        LevelEndScreen();
        ~LevelEndScreen();

        void Show(bool levelComplete);

        void Update();
        void Draw();

    private:
        bool moveUp;

        LevelEndState state;

        TextBox *textBox;

        void UpdateReveal();
        void UpdateMessage();
        void UpdateReset();

        void DrawDialogue();
};

#endif // LevelEndScreen_H