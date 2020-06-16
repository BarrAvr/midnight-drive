#pragma once
#include <vector>
#include <fstream>
#include "Score.h"

class Scoreboard
{
public:
    Scoreboard();
    ~Scoreboard() = default;
    using scorePair = std::pair<Score, std::string>;

    void readScoresFromFile(const std::string& fileName);
    void writeScoresToFile(const std::string& fileName);
    void addScore(const Score& score, const std::string& name);
    bool contains(const Score& score, const std::string& name);

    std::vector<scorePair> getScores() { return scores; }
    friend std::ostream& operator<<(std::ostream& out, Scoreboard& s);

private:
    std::vector<scorePair> scores;
    void addScore(const scorePair&);
};
