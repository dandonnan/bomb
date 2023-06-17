#include "../../include/ui/scoreWindow.h"

#include "../../include/system/gameFactory.h"

ScoreWindow::ScoreWindow()
{
    backgrounds =
    {
        GameFactory::GetSprite(UIFile, "ScoreWindowTop", new Vector2(50, 394)),
        GameFactory::GetSprite(UIFile, "ScoreWindowMiddle", new Vector2(50, 490)),
        GameFactory::GetSprite(UIFile, "ScoreWindowBottom", new Vector2(50, 586))
    };

    text =
    {
        GameFactory::GetText(ReplaceText(GameFactory::GetLocalisedString("Level"), "1"), 30, new Vector2(60, 430)),
        GameFactory::GetText(ReplaceText(GameFactory::GetLocalisedString("ScoreLevel"), "0"), 30, new Vector2(60, 526)),
        GameFactory::GetText(GameFactory::GetLocalisedString("ScoreTotal"), 30, new Vector2(60, 600)),
        GameFactory::GetText("0", 30, new Vector2(60, 635))
    };
}

ScoreWindow::~ScoreWindow()
{
    for (int i = 0; i < (int)backgrounds.size(); i++)
    {
        delete backgrounds.at(i);
    }

    for (int i = 0; i < (int)text.size(); i++)
    {
        delete text.at(i);
    }

    backgrounds.clear();
    text.clear();
}

void ScoreWindow::SetLevel(int level)
{
    text.at(0)->UpdateText(ReplaceText(GameFactory::GetLocalisedString("Level"), std::to_string(level)));
}

void ScoreWindow::UpdateScore(int score, int total)
{
    text.at(1)->UpdateText(ReplaceText(GameFactory::GetLocalisedString("ScoreLevel"), std::to_string(score)));
    text.at(3)->UpdateText(std::to_string(total));
}

void ScoreWindow::Draw()
{
    for (int i = 0; i < (int)backgrounds.size(); i++)
    {
        backgrounds.at(i)->Draw();
    }

    for (int i = 0; i < (int)text.size(); i++)
    {
        text.at(i)->Draw();
    }
}

std::string ScoreWindow::ReplaceText(std::string source, std::string value)
{
    int index = source.find("{0}");

    return source.replace(index, 3, value);
}