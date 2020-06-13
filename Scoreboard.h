#pragma once
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Scoreboard
{

public:
    using Score = pair<int, string>;
    Scoreboard() ;

    void readScoresFromFile(const string& fileName);
    void writeScoresToFile(const string& fileName);

    ~Scoreboard() = default;
    void addScore(const Score&);
    void addScore(int score, const string& name);
    bool contains(int score, const std::string& name);

    vector<Score> getScores() { return scores; }
    friend ostream& operator<<(ostream& out, Scoreboard& s);

private:
    vector<Score> scores;
};

#endif //SCOREBOARD_H