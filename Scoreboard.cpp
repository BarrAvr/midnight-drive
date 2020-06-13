#include <iostream>
#include <algorithm>
#include "Scoreboard.h"
#include "Constants.h"

namespace cs = constants;

//add score by score pair
void Scoreboard::addScore(const Scoreboard::Score& s)
{
    // Add score
    scores.push_back(s);
    // Sort highest to lowest
    sort(scores.begin(), scores.end(), greater<>());
}

//add score by score and name
void Scoreboard::addScore(int score, const string& name)
{
    Score temp;
    temp.first = score;
    temp.second = name;

    if (!contains(score, name))
        scores.push_back(temp);

    sort(scores.begin(), scores.end(), greater<>());

}

//a function to see if it already contains the same entree
bool Scoreboard::contains(int score, const std::string& name)
{
    for (auto& s : scores)
        if (s.first == score && s.second == name)
            return true;

    return false;

}

//assuming everything on the text file is in format:
/*
score,name
1,p a t
200,83owpe
*/
void Scoreboard::readScoresFromFile(const string& fileName)
{
    ifstream fin(fileName);//assuming each score is stored score, name

    if (!fin)
    {
        //THROW EXCEPTION HERE
    } else
    {
        while (!fin.eof())
        {
            string scoreTemp, nameTemp;
            getline(fin, scoreTemp, ',');
            getline(fin, nameTemp);
            Score add;
            add.first = stoi(scoreTemp);
            add.second = nameTemp;

            addScore(add);
        }
    }
}


void Scoreboard::writeScoresToFile(const string& fileName)
{
    ofstream fout(fileName);

    fout << this;

    fout.close();
}


Scoreboard::Scoreboard()
{
    Score defaultScore;
    defaultScore.first = 0;
    defaultScore.second = "-----";
    for (auto i = 0; i < 10; i++)
    {
        scores.push_back(defaultScore);
    }


    //read from the file
    readScoresFromFile(cs::ResourcePath + "inputScoreFile.txt");

    //write to the file
    writeScoresToFile(cs::ResourcePath + "inputScoreFile.txt");
}

ostream& operator<<(ostream& out, Scoreboard& s)
{
    for (auto& score : s.getScores())
    {
        //we dont want to be outputting any "0,-----" to the file
        if (!(score.first == 0 && score.second == "-----"))
            out << score.first << "," << score.second << std::endl;
    }
    return out;
}
