#include "Trashcan.h"
#include "Constants.h"

Trashcan::Trashcan(Score& score) : Obstacle(score, 2) 
{
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[0])) {
        throw "Trashcan Image Not Found";
    }
    obstacle_.setScale(sf::Vector2f(cs::obstacleSize, cs::obstacleSize));
    obstacle_.setTexture(texture_);
    if (!crashBuffer.loadFromFile(constants::ResourcePath + constants::BigCrashSound)) {
        throw "Trashcan crash sound Not Found";
    }
    crashSound.setBuffer(crashBuffer);
}


void Trashcan::makeCrashSound() 
{
    crashSound.setVolume(50);
    crashSound.setPitch(crashSound.getPitch());
    crashSound.play();
}