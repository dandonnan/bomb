#include "../graphics/sprite.h"

#include "../graphics/displayText.h"

#include <vector>

#ifndef ScoreWindow_H
#define ScoreWindow_H

// A window that displays scores.
class ScoreWindow
{
    public:
        ScoreWindow();
        ~ScoreWindow();

        void SetLevel(int level);
        void UpdateScore(int level, int total);

        void Draw();

    private:
        std::vector<Sprite*> backgrounds;
        std::vector<DisplayText*> text;

        std::string ReplaceText(std::string source, std::string value);
};

#endif // ScoreWindow_H