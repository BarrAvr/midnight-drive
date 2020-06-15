#include "Pothole.h"
#include "Constants.h"

Pothole::Pothole(Score& score) : Obstacle(score, 1) 
{
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[4])) {
        throw "Pothole Image Not Found";
    }
    obstacle_.setScale(sf::Vector2f(cs::obstacleSize, cs::obstacleSize));
    obstacle_.setTexture(texture_);
    if (!crashBuffer.loadFromFile(constants::ResourcePath + constants::SmallCrashSound)) {
        throw "Pothole crash sound Not Found";
    }
    crashSound.setBuffer(crashBuffer);
}

void Pothole::makeCrashSound() 
{
    crashSound.setVolume(50);
    crashSound.play();
}