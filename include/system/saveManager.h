#include "gameSaveData.h"

#define SaveDataFile    "sdmc:/switch/bombflip.dat"

#ifndef SaveManager_H
#define SaveManager_H

// A manager for saving / loading data.
class SaveManager{
    public:
        static SaveManager *GetInstance();

        SaveManager(SaveManager &other) = delete;
        void operator=(const SaveManager &) = delete;

        GameSaveData *Data();

        void Save();
        void Load();

    protected:
        SaveManager() {}
        ~SaveManager() {}

    private:
        static SaveManager *instance;

        GameSaveData* data;
};

#endif // SaveManager_H
