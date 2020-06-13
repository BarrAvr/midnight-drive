#include "cone.h"
#include "Constants.h"

Cone::Cone() {// : Obstacle() {
    damage_level = 20;
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[1])) {
        throw "Cone Image Not Found";
    }
    obstacle_.setSize(sf::Vector2f(constants::obstacleSize, constants::obstacleSize));
    obstacle_.setTexture(&texture_);
    if (!crashBuffer.loadFromFile(constants::ResourcePath + constants::SmallCrashSound)) {
        throw "Cone crash sound Not Found";
    }
    crashSound.setBuffer(crashBuffer);
}

Cone::Cone(float x, float y, float width, float height, int damage_level) : Obstacle() {
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[1])) {
        throw "Cone Image Not Found";
    }
}

void Cone::makeCrashSound() {
    crashSound.setVolume(50);
    crashSound.play();
}