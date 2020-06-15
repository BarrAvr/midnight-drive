#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Score.h"

class Scoreboard
{
public:
    using scorePair = std::pair<Score, std::string>;
    Scoreboard();

    void readScoresFromFile(const std::string& fileName);
    void writeScoresToFile(const std::string& fileName);

    ~Scoreboard() = default;
    void addScore(const Score& score, const std::string& name);
    bool contains(const Score& score, const std::string& name);

    std::vector<scorePair> getScores() { return scores; }
    friend std::ostream& operator<<(std::ostream& out, Scoreboard& s);

private:
    void addScore(const scorePair&);
    std::vector<scorePair> scores;
};
