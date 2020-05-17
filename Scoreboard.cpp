#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Scoreboard.h"
#include <sstream>

void Scoreboard::addScore(const Scoreboard::Score& s)
{
    // Add score
    scores.push_back(s);
    // Sort highest to lowest
    sort(scores.begin(), scores.end(), greater<>());
}

// Print high scores
sf::String Scoreboard::printScores()
{
    std::ostringstream sout;
    sout << "***************** High Scores ******************" << endl;
    sout << "Name    Score" << endl;
    for (int i = 0; i < 3; i++)
    {
        sout << scores[i].second << " : ";
        sout << scores[i].first << endl;
    }
    return sout.str();
}




