#include "../../include/audio/audioManager.h"

#include "../../include/system/saveManager.h"
#include "../../include/system/sdlLibrary.h"

#include <SDL_mixer.h>

AudioManager *AudioManager::instance{nullptr};

/// @brief Get the instance of the audio manager.
/// @return The audio manager instance.
AudioManager *AudioManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new AudioManager();
    }

    return instance;
}

/// @brief Play a music track.
///        The track will only start if music is enabled.
/// @param track The name of the track.
void AudioManager::PlayMusic(std::string track)
{
    if (SaveManager::GetInstance()->Data()->MusicOn())
    {
        Mix_PlayMusic(SDLLibrary::GetMusic(track), -1);
    }
}

/// @brief Stop music from playing.
void AudioManager::StopMusic()
{
    Mix_HaltMusic();
}

/// @brief Play a sound effect.
///        The sound will only play if sounds are enabled.
/// @param sound The name of the sound effect.
void AudioManager::PlaySoundEffect(std::string sound)
{
    if (SaveManager::GetInstance()->Data()->SoundOn())
    {
        Mix_PlayChannel(-1, SDLLibrary::GetSound(sound), 0);
    }
}