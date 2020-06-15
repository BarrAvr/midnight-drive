#pragma once

#include <SFML/Graphics.hpp>
#include "Drawable.h"

class Score : public virtual Drawable
{
private:
    int score_ = 0;
    sf::Text scoreText;
    sf::Font font;
public:
    Score();
    ~Score() = default;
    explicit Score(int score) : score_(score) {}
    void addToScore();
    void draw(sf::RenderWindow& window) override;

    int getScore() const { return score_; }

    friend bool operator<(const Score& a, const Score& b);
};
