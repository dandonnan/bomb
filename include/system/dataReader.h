#include <SDL.h>

#include <string>
#include <map>

#ifndef DataReader_H
#define DataReader_H

// Reads in data from files in the romfs folder.
class DataReader
{
    public:
        static std::map<std::string, std::string> ReadFileAsMap(std::string filename);

        static SDL_Rect ParseRectangleFromString(std::string string);

    private:
        static std::string GetStringInQuotes(std::string line);
};

#endif // DataReader_H