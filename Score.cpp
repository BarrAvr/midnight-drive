#include "Score.h"
#include "Constants.h"

namespace cs = constants;

Score::Score()
{
    font.loadFromFile(cs::RESOURCE_PATH + cs::FONT);
    scoreText.setFont(font);
    scoreText.setCharacterSize(60);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(30, 90);
}

void Score::draw(sf::RenderWindow& window)
{
    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);
}

void Score::addToScore()
{
    score += 5;
}

bool operator<(const Score& a, const Score& b)
{
    return a.score < b.score;
}
