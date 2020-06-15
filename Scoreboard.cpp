#include <iostream>
#include <algorithm>
#include "Scoreboard.h"
#include "Constants.h"

namespace cs = constants;

//add score by score pair
void Scoreboard::addScore(const Scoreboard::scorePair& s)
{
    // Add score
    scores.push_back(s);
    // Sort highest to lowest
    sort(scores.begin(), scores.end(), std::greater<>());
}

//add score by score and name
void Scoreboard::addScore(const Score& score, const std::string& name)
{
    scorePair temp;
    temp.first = score;
    temp.second = name;

    if (!contains(score, name))
        scores.push_back(temp);

    sort(scores.begin(), scores.end(), std::greater<>());

}

//a function to see if it already contains the same entree
bool Scoreboard::contains(const Score& score, const std::string& name)
{
    for (auto& s : scores)
        if (s.first.getScore() == score.getScore() && s.second == name)
            return true;

    return false;

}

//assuming everything on the text file is in format:
/*
score,name
1,p a t
200,83owpe
*/
void Scoreboard::readScoresFromFile(const std::string& fileName)
{
    std::ifstream fin(fileName);//assuming each score is stored score, name

    if (!fin)
    {
        //THROW EXCEPTION HERE
    } else
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

std::ostream& operator<<(std::ostream& out, Scoreboard& s)
{
    for (auto& score : s.getScores())
    {
        //we dont want to be outputting any "0,-----" to the file
        if (!(score.first.getScore() == 0 && score.second == "-----"))
        {
            out << score.first.getScore() << "," << score.second << std::endl;
        }
    }
    return out;
}

