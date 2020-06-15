#include "cone.h"
#include "Constants.h"

Cone::Cone(Score& score) : Obstacle(score, 1) 
{
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[1])) {
        throw "Cone Image Not Found";
    }
    obstacle_.setScale(sf::Vector2f(cs::obstacleSize, cs::obstacleSize));
    obstacle_.setTexture(texture_);
    if (!crashBuffer.loadFromFile(constants::ResourcePath + constants::SmallCrashSound)) {
        throw "Cone crash sound Not Found";
    }
    crashSound.setBuffer(crashBuffer);
}


void Cone::makeCrashSound() 
{
    crashSound.setVolume(50);
    crashSound.play();
}