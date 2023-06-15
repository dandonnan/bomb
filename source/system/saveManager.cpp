#include "../../include/system/saveManager.h"

#include <string>
#include <stdio.h>
#include <sys/stat.h>

SaveManager *SaveManager::instance{nullptr};

/// @brief Get the instance of the save manager.
/// @return The save manager instance.
SaveManager *SaveManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new SaveManager();
        instance->Load();
    }

    return instance;
}

/// @brief Get the save data.
/// @return The save data.
GameSaveData* SaveManager::Data()
{
    return data;
}

/// @brief Save the game.
void SaveManager::Save()
{
    // Creates directory for storing the file in
    mkdir("sdmc:/switch", 777);

    // Create and open a file for writing
    FILE *file = fopen(SaveDataFile, "w");

    // The file will only contain three values - an integer determining
    // whether sound is on, an integer determining whether music is
    // on, and a comma separating the two
    // If it contained more data, the GameSaveData object could be
    // serialised in a much better way and the serialised string could
    // be written out instead
    fprintf(file, "%i%c%i", data->MusicOn() ? 1 : 0, ',', data->SoundOn() ? 1 : 0);

    fclose(file);
}

/// @brief Load the game.
void SaveManager::Load()
{
    data = new GameSaveData();

    // Open the file for reading
    // The file should only contain three values (e.g. 0,1)
    // where two integers are separated by a comma. The integers
    // will determine whether sound effects and music should
    // be enabled.
    
    FILE *file = fopen(SaveDataFile, "r");

    if (file == NULL)
    {
        fclose(file);
        return;
    }

    char contents[1024];

    // Read the file to the contents buffer
    while (fgets(contents, sizeof(contents), file))
    {
        // Read the line
        std::string line = contents;

        // Read the first character
        if (line.substr(0, 1) == "0")
        {
            // If it is 0, toggle music to be off
            data->ToggleMusic();
        }

        // Read the third character
        if (line.substr(2,1) == "0")
        {
            // If it is 0, toggle sound to be off
            data->ToggleSound();
        }
    }

    fclose(file);
}