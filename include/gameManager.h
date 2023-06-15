#include "system/gameFactory.h"
#include "scenes/scenes.h"
#include "scenes/scene.h"

#include <string>

#ifndef GameManager_H
#define GameManager_H

// The game manager that handles what scene is active.
class GameManager
{
    public:
        GameManager(std::string version);
        ~GameManager();
        void Update();
        void Draw();

        void SetGridSize(int size);
        int GetGridSize();

        void ChangeScene(Scenes nextScene);

    private:
        Scene* scene;

        std::string version;

        int gridSize;
};

#endif // GameManager_H