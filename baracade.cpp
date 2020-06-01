#include "baracade.h"

Baracade::Baracade(float x, float y, float width, float height, int damage_level) : Obstacle(x, y, width, height, damage_level) {
    if (!texture.loadFromFile("C:\\Users\\Barr Avrahamov\\source\\repos\\SFML_Stuff\\SFML_Stuff\\Car game v4\\Construction objects\\Street baracade.png")) {
        throw "Baracade Image Not Found";
    }
}

void Baracade::makeCrashSound(sf::RenderWindow& window) {
    //need to copy sound here
    std::cout << "baracade crash noise" << std::endl;
}