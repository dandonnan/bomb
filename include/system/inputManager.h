#include "core.h"
#include "../graphics/vector2.h"

#include <SDL.h>

#include <switch.h>

#define MaxInputSize    28  // The maximum number of button inputs.

#ifndef InputManager_H
#define InputManager_H

// The input manager.
class InputManager
{
    public:
        static InputManager *GetInstance();

        InputManager(InputManager &other) = delete;
        void operator=(const InputManager &) = delete;

        bool IsInputPressed(int keyCode);
        bool IsInputHeld(int keyCode);
        bool IsInputReleased(int keyCode);
        bool AnyKey();
        bool IsTouched();
        Vector2* GetTouchPosition();
        void Update(SDL_Event event);

    protected:
        InputManager() {}
        ~InputManager() {}

    private:
        static InputManager *instance;

        HidTouchScreenState touchState;

        bool currentState[MaxInputSize];
        bool lastState[MaxInputSize];
        void Initialise();
};

#endif // InputManager_H