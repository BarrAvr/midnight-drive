#pragma once
#include <SFML/Graphics.hpp>
#include "Drawable.h"

class Score : public virtual Drawable
{
private:
    int score = 0;
    sf::Text scoreText;
    sf::Font font;
public:
    Score();
    ~Score() = default;
    explicit Score(int score) : score(score) {}
    void draw(sf::RenderWindow& window) override;
    void addToScore();
    int getScore() const { return score; }
    friend bool operator<(const Score& a, const Score& b);
};
