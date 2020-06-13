#include "gasoline.h"
#include "Constants.h"

Gasoline::Gasoline() {// : Obstacle() {
    damage_level = -10;
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[3])) {
        throw "Gasoline Image Not Found";
    }
    obstacle_.setSize(sf::Vector2f(constants::obstacleSize, constants::obstacleSize));
    obstacle_.setTexture(&texture_);
    if (!crashBuffer.loadFromFile(constants::ResourcePath + constants::GasCrashSound)) {
        throw "Gasoline crash sound Not Found";
    }
    crashSound.setBuffer(crashBuffer);
}

Gasoline::Gasoline(float x, float y, float width, float height, int damage_level) : Obstacle() {
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[3])) {
        throw "Gasoline Image Not Found";
    }
}

void Gasoline::makeCrashSound() {
    crashSound.play();
}