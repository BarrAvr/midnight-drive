#include "Trashcan.h"
#include "Constants.h"

Trashcan::Trashcan() {// : Obstacle() {
    damage_level = 30;
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[0])) {
        throw "Trashcan Image Not Found";
    }
    obstacle_.setSize(sf::Vector2f(constants::obstacleSize, constants::obstacleSize));
    obstacle_.setTexture(&texture_);
    if (!crashBuffer.loadFromFile(constants::ResourcePath + constants::BigCrashSound)) {
        throw "Trashcan crash sound Not Found";
    }
    crashSound.setBuffer(crashBuffer);
}

Trashcan::Trashcan(float x, float y, float width, float height, int damage_level) : Obstacle() {
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[0])) {
        throw "Trashcan Image Not Found";
    }
    obstacle_.setSize(sf::Vector2f(constants::obstacleSize, constants::obstacleSize));
    obstacle_.setTexture(&texture_);
}

void Trashcan::makeCrashSound() {
    crashSound.setVolume(50);
    crashSound.setPitch(crashSound.getPitch());
    crashSound.play();
}