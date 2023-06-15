#include <string>

#ifndef AudioManager_H
#define AudioManager_H

// A manager for audio events.
class AudioManager
{
    public:
        static AudioManager *GetInstance();

        AudioManager(AudioManager &other) = delete;
        void operator=(const AudioManager &) = delete;

        void PlayMusic(std::string track);
        void StopMusic();

        void PlaySoundEffect(std::string sound);

    protected:
        AudioManager() {}
        ~AudioManager() {}

    private:
        static AudioManager *instance;
};

#endif // AudioManager_H