#include "gasoline.h"
#include "Constants.h"

Gasoline::Gasoline(Score& score) : Obstacle(score, -1) 
{
    if (!texture_.loadFromFile(cs::ResourcePath + cs::PATHS[3])) {

        throw "Gasoline Image Not Found";
    }

    obstacle_.setScale(sf::Vector2f(cs::obstacleSize, cs::obstacleSize));
    obstacle_.setTexture(texture_);
    if (!crashBuffer.loadFromFile(constants::ResourcePath + constants::GasCrashSound)) {
        throw "Gasoline crash sound Not Found";
    }
    crashSound.setBuffer(crashBuffer);
}


void Gasoline::makeCrashSound() {
    crashSound.play();
}