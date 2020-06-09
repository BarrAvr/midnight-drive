#include "gasoline.h"
#include "Constants.h"

Gasoline::Gasoline() : Obstacle() {
    damage_level = -10;
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[3])) {
        throw "Gasoline Image Not Found";
    }
}

Gasoline::Gasoline(float x, float y, float width, float height, int damage_level) : Obstacle() {
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[3])) {
        throw "Gasoline Image Not Found";
    }
}

void Gasoline::makeCrashSound(sf::RenderWindow& window) {
    //need to copy sound here
    std::cout << "Gasoline crash noise" << std::endl;
}