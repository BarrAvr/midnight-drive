#include "baracade.h"
#include "Constants.h"

Baracade::Baracade() : Obstacle() {
    damage_level = 50;
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[2])) {
        throw "Baracade Image Not Found";
    }
}

Baracade::Baracade(float x, float y, float width, float height, int damage_level) : Obstacle() {
    if (!texture_.loadFromFile(constants::ResourcePath + constants::PATHS[2])) {
        throw "Baracade Image Not Found";
    }
}

void Baracade::makeCrashSound(sf::RenderWindow& window) {
    //need to copy sound here
    std::cout << "baracade crash noise" << std::endl;
}