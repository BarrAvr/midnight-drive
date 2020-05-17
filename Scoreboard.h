#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

class Scoreboard
{
public:
    using Score = pair<int, string>;
    Scoreboard() = default;
    ~Scoreboard() = default;
    void addScore(const Score&);
    sf::String printScores();

private:
    vector<Score> scores;
};

#endif //SCOREBOARD_H
