#include "../../include/system/gameSaveData.h"
#include "../../include/system/saveManager.h"

/// @brief Create a new save data object.
GameSaveData::GameSaveData()
{
    SetToDefault();
}

/// @brief Destroy the save data object.
GameSaveData::~GameSaveData()
{
}

/// @brief Set the data to the default.
void GameSaveData::SetToDefault()
{
    musicOn = true;
    soundOn = true;
}

/// @brief Get whether music is turned on.
/// @return true if turned on. false if not.
bool GameSaveData::MusicOn()
{
    return musicOn;
}

/// @brief Get whether sound effects are turned on.
/// @return true if turned on. false if not.
bool GameSaveData::SoundOn()
{
    return soundOn;
}

/// @brief Toggle the music.
void GameSaveData::ToggleMusic()
{
    musicOn = !musicOn;
}

/// @brief Toggle the sound effects.
void GameSaveData::ToggleSound()
{
    soundOn = !soundOn;
}