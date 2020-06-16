#include <iostream>
#include <algorithm>
#include "Scoreboard.h"
#include "FileNotFound.h"

namespace cs = constants;

Scoreboard::Scoreboard()
{
    scorePair defaultScore;
    defaultScore.first = Score(0);
    defaultScore.second = "-----";
    for (auto i = 0; i < 10; i++)
    {
        scores.push_back(defaultScore);
    }
}

/*
Expected Text File Format:
score,name
1,p a t
200,83owpe
*/
void Scoreboard::readScoresFromFile(const std::string& fileName)
{
    std::ifstream fin(fileName); // assuming each score is stored score, name

    if (!fin)
    {
        try { throw FileNotFound(fileName); }
        catch (FileNotFound e)
        {
            std::cout << e.what();
            std::string path = e.resolve();
            fin.open(fileName);
        }
    }
    else
    {
        std::string scoreTemp, nameTemp;
        while (getline(fin, scoreTemp, ','))
        {
            getline(fin, nameTemp);
            scorePair add = std::make_pair(Score(stoi(scoreTemp)), nameTemp);
            addScore(add);
        }
    }
}

void Scoreboard::writeScoresToFile(const std::string& fileName)
{
    std::ofstream fout(fileName);
    fout << *this;
    fout.close();
}

// add score by score pair
void Scoreboard::addScore(const Scoreboard::scorePair& s)
{
    scores.push_back(s);
    sort(scores.begin(), scores.end(), std::greater<>());    // Sort highest to lowest
}

// add score by score and name
void Scoreboard::addScore(const Score& score, const std::string& name)
{
    scorePair temp;
    temp.first = score;
    temp.second = name;

    if (!contains(score, name))
        scores.push_back(temp);

    sort(scores.begin(), scores.end(), std::greater<>());
}

// a function to see if it already contains the same entree
bool Scoreboard::contains(const Score& score, const std::string& name)
{
    for (auto& s : scores)
        if (s.first.getScore() == score.getScore() && s.second == name)
            return true;

    return false;
}

std::ostream& operator<<(std::ostream& out, Scoreboard& s)
{
    for (auto& score : s.getScores())
    {
        if (!(score.first.getScore() == 0))
        {
            out << score.first.getScore() << ",";
            if (!(score.second != ""))
            {
                out << "Anonymous" << std::endl;
            }
            else
            {
                out << score.second << std::endl;
            }
        }
    }
    return out;
}

