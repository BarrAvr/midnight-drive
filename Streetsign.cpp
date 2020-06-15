#include "Streetsign.h"
#include "Constants.h"

Streetsign::Streetsign(Score& score) : Obstacle(score, 3) 
{
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[5])) {
        throw "Streetsign Image Not Found";
    }
    obstacle_.setScale(sf::Vector2f(cs::obstacleSize, cs::obstacleSize));
    obstacle_.setTexture(texture_);
    if (!crashBuffer.loadFromFile(constants::ResourcePath + constants::BigCrashSound)) {
        throw "Streetsign crash sound Not Found";
    }
    crashSound.setBuffer(crashBuffer);
}


void Streetsign::makeCrashSound() 
{
    crashSound.setVolume(50);
    crashSound.setPitch(crashSound.getPitch() * 0.5);
    crashSound.play();
}