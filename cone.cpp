#include "cone.h"
#include "Constants.h"

Cone::Cone() : Obstacle() {
    damage_level = 20;
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[1])) {
        throw "Cone Image Not Found";
    }
}

Cone::Cone(float x, float y, float width, float height, int damage_level) : Obstacle() {
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[1])) {
        throw "Cone Image Not Found";
    }
}

void Cone::makeCrashSound(sf::RenderWindow& window) {
    //need to copy sound here
    std::cout << "cone crash noise" << std::endl;
}