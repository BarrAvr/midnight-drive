#include "baracade.h"
#include "Constants.h"

Baracade::Baracade(Score& score) : Obstacle(score, 3) 
{
    if (!texture_.loadFromFile(cs::ResourcePath + cs::PATHS[2])) {
        throw "Baracade Image Not Found";
    }
    obstacle_.setScale(sf::Vector2f(cs::obstacleSize, cs::obstacleSize));
    obstacle_.setTexture(texture_);
    if (!crashBuffer.loadFromFile(cs::ResourcePath + cs::BigCrashSound)) {
        throw "Baracade crash sound Not Found";
    }
    crashSound.setBuffer(crashBuffer);
}

void Baracade::makeCrashSound() 
{
    crashSound.setVolume(50);
    crashSound.setPitch(crashSound.getPitch() * 0.5);
    crashSound.play();
}