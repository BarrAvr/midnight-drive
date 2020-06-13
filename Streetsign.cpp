#include "Streetsign.h"
#include "Constants.h"

Streetsign::Streetsign() {// : Obstacle() {
    damage_level = 50;
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[5])) {
        throw "Streetsign Image Not Found";
    }
    obstacle_.setSize(sf::Vector2f(constants::streetSignSize, constants::streetSignSize));
    obstacle_.setTexture(&texture_);
    if (!crashBuffer.loadFromFile(constants::ResourcePath + constants::BigCrashSound)) {
        throw "Streetsign crash sound Not Found";
    }
    crashSound.setBuffer(crashBuffer);
}

Streetsign::Streetsign(float x, float y, float width, float height, int damage_level) : Obstacle() {
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[5])) {
        throw "Streetsign Image Not Found";
    }
    obstacle_.setSize(sf::Vector2f(constants::obstacleSize, constants::obstacleSize));
    obstacle_.setTexture(&texture_);
}

void Streetsign::makeCrashSound() {
    crashSound.setVolume(50);
    crashSound.setPitch(crashSound.getPitch() * 0.5);
    crashSound.play();
}