#include "baracade.h"
#include "Constants.h"

Baracade::Baracade() {// : Obstacle() {
    damage_level = 50;
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[2])) {
        throw "Baracade Image Not Found";
    }
    obstacle_.setSize(sf::Vector2f(constants::obstacleSize, constants::obstacleSize));
    obstacle_.setTexture(&texture_);
    if (!crashBuffer.loadFromFile(constants::ResourcePath + constants::BigCrashSound)) {
        throw "Baracade crash sound Not Found";
    }
    crashSound.setBuffer(crashBuffer);
}

Baracade::Baracade(float x, float y, float width, float height, int damage_level) : Obstacle() {
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[2])) {
        throw "Baracade Image Not Found";
    }
}

void Baracade::makeCrashSound() {
    crashSound.setVolume(50);
    crashSound.setPitch(crashSound.getPitch() * 0.5);
    crashSound.play();
}