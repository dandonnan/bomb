#include "../gameManager.h"
#include "../graphics/sprite.h"
#include "../ui/button.h"
#include "../ui/optionsMenu.h"
#include "scenes.h"

#include <vector>
#include <string>

#ifndef TitleScene_H
#define TitleScene_H

// The game's title screen.
class TitleScene : public Scene
{
    public:
        TitleScene(GameManager* game, std::string version);
        virtual ~TitleScene();
        void Update();
        void Draw();

    private:
        Sprite *background;
        Sprite *logo;
        GameManager *gameManager;

        std::vector<DisplayText*> strings;
};

#endif // TitleScene_H