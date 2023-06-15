#include "../../include/system/inputManager.h"

InputManager *InputManager::instance{nullptr};

/// @brief Get the instance of the input manager.
/// @return The input manager instance.
InputManager *InputManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new InputManager();
        instance->Initialise();
    }

    return instance;
}

/// @brief Get whether an input has been pressed this frame.
/// @param inputCode The code corresponding to an input.
/// @return true if the input is pressed. false if not.
bool InputManager::IsInputPressed(int inputCode)
{
    return currentState[inputCode] && !lastState[inputCode];
}

/// @brief Get whether an input is held.
/// @param inputCode The code corresponding to an input.
/// @return true if the input is held. false if not.
bool InputManager::IsInputHeld(int inputCode)
{
    return currentState[inputCode] && lastState[inputCode];
}

/// @brief Get whether an input has been released this frame.
/// @param inputCode The code corresponding to an input.
/// @return true if the input is released. false if not.
bool InputManager::IsInputReleased(int inputCode)
{
    return !currentState[inputCode] && lastState[inputCode];
}

/// @brief Get whether any key has been pressed.
/// @return true if any key is pressed. false if not.
bool InputManager::AnyKey()
{
    for (int i = 0; i < MaxInputSize; i++)
    {
        if (currentState[i])
        {
            return true;
        }
    }

    return false;
}

/// @brief Get whether the screen is touched.
/// @return true if the screen is touched. false if not.
bool InputManager::IsTouched()
{
    return touchState.count > 0;
}

/// @brief Get the position where the screen was touched.
/// @return The position where the screen was touched, or (0,0) as the default.
Vector2* InputManager::GetTouchPosition()
{
    if (touchState.count > 0)
    {
        return new Vector2(touchState.touches[0].x, touchState.touches[0].y);
    }

    return new Vector2(0, 0);
}

/// @brief Update the inputs to check the current states.
/// @param event The SDL event.
void InputManager::Update(SDL_Event event)
{
    // Set the last states
    for (int i = 0; i < MaxInputSize; i++)
    {
        lastState[i] = currentState[i];
    }

    // If a button is pressed, set the state of that button
    if (event.type == SDL_JOYBUTTONDOWN)
    {
        currentState[event.jbutton.button] = true;
    }

    // If a button is released, set the state of that button
    if (event.type == SDL_JOYBUTTONUP)
    {
        currentState[event.jbutton.button] = false;
    }

    touchState = {0};

    // Get the touch screen state
    hidGetTouchScreenStates(&touchState, 1);
}

/// @brief Initialise the input manager.
void InputManager::Initialise()
{
    for (int i = 0; i < MaxInputSize; i++)
    {
        currentState[i] = false;
        lastState[i] = false;
    }

    touchState = {0};
}