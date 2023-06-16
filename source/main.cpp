// This is the main entry point for the game

#include <unistd.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>

#include <switch.h>

#include <string>

#include "../../include/system/core.h"
#include "../../include/graphics/displayText.h"
#include "../../include/system/dataReader.h"
#include "../../include/system/gameFactory.h"
#include "../../include/system/sdlLibrary.h"
#include "../../include/graphics/sprite.h"
#include "../../include/gameManager.h"
#include "../../include/system/inputManager.h"
#include "../../include/events/eventManager.h"
#include "../../include/events/knownEvents.h"

#define VersionNumber   "1.0.1"       // The game's version number

int quit = 0;
int refreshRate = 24;
GameManager* gameManager;

SDL_Renderer *renderer;

/// @brief The method called each frame for updating game objects.
/// @param event The SDL event.
void Update(SDL_Event event)
{
    // This will close the game, although it is never triggered naturally
    if (event.type == SDL_QUIT)
    {
        quit = 1;
    }

    InputManager::GetInstance()->Update(event);

    gameManager->Update();
}

/// @brief The method called each frame for rendering to the screen.
void Draw()
{
    SDL_RenderClear(renderer);    

    gameManager->Draw();

    SDL_RenderPresent(renderer);

    SDL_Delay(refreshRate);
}

/// @brief The main entry point.
/// @param argc Arguments.
/// @param argv Arguments.
/// @return Returns 0 when the game has finished.
int main(int argc, char* argv[])
{
    // Initialise the ROM file system
    romfsInit();

    // Change the directory to go to the game's ROMFS folder
    chdir("romfs:/");

    SDL_Event event;

    // Initialise various graphics libraries
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    Mix_Init(MIX_INIT_OGG);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    // Create the game window
    SDL_Window *window = SDL_CreateWindow("Bomb Flip", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                            SCREEN_WIDTH_DOCKED, SCREEN_HEIGHT_DOCKED, SDL_WINDOW_SHOWN);

    // Create a renderer for the game window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    // Initialise input
    SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    SDL_JoystickEventState(SDL_ENABLE);
    SDL_JoystickOpen(0);

    // Initialise audio
    SDL_InitSubSystem(SDL_INIT_AUDIO);
    Mix_AllocateChannels(3);
    Mix_OpenAudio(48000, AUDIO_S16, 2, 4096);

    // Initialise the touch screen (although this is not used)
    hidInitializeTouchScreen();

    // Initialise game factories and libraries
    GameFactory::Initialise(renderer);
    SDLLibrary::Initialise(renderer);

    // Create the game manager
    gameManager = new GameManager(VersionNumber);

    // As long as the game is running, call the Update and Draw functions
    while (!quit && appletMainLoop())
    {
        while (SDL_PollEvent(&event))
        {
            Update(event);
        }

        Draw();
    }

    // Do garbage collection on the game
    SDLLibrary::Clear();
    gameManager->~GameManager();

    delete gameManager;

    // Close the other game systems
    Mix_HaltChannel(-1);

    IMG_Quit();
    Mix_CloseAudio();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
    romfsExit();

    return 0;
}