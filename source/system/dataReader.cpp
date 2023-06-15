#include "../../include/system/dataReader.h"

#include <cstring>
#include <stdio.h>

/// @brief Read in a file and convert it to a data map.
///        The file should be in a key-value format ("key": "value").
/// @param fileName The name of the file.
/// @return The file as a map
std::map<std::string, std::string> DataReader::ReadFileAsMap(std::string fileName)
{
    std::map<std::string, std::string> map;

    // Open the file
    FILE *file = fopen(fileName.c_str(), "r");

    char contents[1024];

    if (file)
    {
        // Read the file 1024 bytes at a time
        while (fgets(contents, sizeof(contents), file))
        {
            std::string line = contents;

            // Get the index of the first quote
            int index = line.find('"');

            // If there is a quote
            if (index >= 0)
            {
                // Get the key from the first set of quotes
                std::string key = GetStringInQuotes(line);

                // Get the index of the colon
                index = line.find(':');

                line = line.substr(index + 1);

                // Get the value from the second set of quotes
                std::string value = GetStringInQuotes(line);

                // Add the key-value pair to the map
                map.insert(std::pair<std::string, std::string>(key, value));
            }
        }

        // Close the file
        fclose(file);
    }

    return map;
}

/// @brief Get a string that is contained within quotes.
/// @param line The line containing a string in quotes.
/// @return The string inside the quotes.
std::string DataReader::GetStringInQuotes(std::string line)
{
    std::string quotes = line;

    // Get the index of the first quote
    int index = quotes.find('"');

    // If there is a quote
    if (index >= 0)
    {
        // Move to after the first quote
        quotes = quotes.substr(index+1);

        // Find the next quote
        index = quotes.find('"');

        // Get the string up to the next quote
        quotes = quotes.substr(0, index);
    }

    return quotes;
}

/// @brief Parse a rectangle from a string.
///        The string should be in the format x,y,w,h
/// @param string The string containing the rectangle.
/// @return A rectangle.
SDL_Rect DataReader::ParseRectangleFromString(std::string string)
{
    int coords[4];

    std::string line = string;

    // For each corner of the rectangle
    for (int i = 0; i < 4; i++)
    {
        std::string number = line;

        // Find the next comma
        int index = line.find(',');

        // If there was a comma, get the value before the comma
        if (index > 0)
        {
            number = line.substr(0, index);
            line = line.substr(index + 1);
        }

        // Convert the string to an integer
        coords[i] = stoi(number);
    }

    return {coords[0], coords[1], coords[2], coords[3]};
}