#ifndef GameSaveData_H
#define GameSaveData_H

// The game's save data.
class GameSaveData {
    public:
        GameSaveData();
        ~GameSaveData();

        bool MusicOn();
        bool SoundOn();

        void ToggleMusic();
        void ToggleSound();

    private:
        bool musicOn;
        bool soundOn;

        void SetToDefault();
};

#endif // GameSaveData_H