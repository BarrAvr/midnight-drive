#include "gasoline.h"

Gasoline::Gasoline(float x, float y, float width, float height, int damage_level) : Obstacle(x, y, width, height, damage_level) {
    if (!texture.loadFromFile("C:\\Users\\Barr Avrahamov\\source\\repos\\SFML_Stuff\\SFML_Stuff\\Car game v4\\Oil can\\oil can shadow.png")) {
        throw "Gasoline Image Not Found";
    }
}

void Gasoline::makeCrashSound(sf::RenderWindow& window) {
    //need to copy sound here
    std::cout << "Gasoline crash noise" << std::endl;
}