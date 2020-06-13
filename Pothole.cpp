#include "Pothole.h"
#include "Constants.h"

Pothole::Pothole() {// : Obstacle() {
    damage_level = 20;
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[4])) {
        throw "Pothole Image Not Found";
    }
    obstacle_.setSize(sf::Vector2f(constants::obstacleSize, constants::obstacleSize));
    obstacle_.setTexture(&texture_);
    if (!crashBuffer.loadFromFile(constants::ResourcePath + constants::SmallCrashSound)) {
        throw "Pothole crash sound Not Found";
    }
    crashSound.setBuffer(crashBuffer);
}

Pothole::Pothole(float x, float y, float width, float height, int damage_level) : Obstacle() {
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[4])) {
        throw "Pothole Image Not Found";
    }
    obstacle_.setSize(sf::Vector2f(constants::obstacleSize, constants::obstacleSize));
    obstacle_.setTexture(&texture_);
}

void Pothole::makeCrashSound() {
    crashSound.setVolume(50);
    crashSound.play();
}