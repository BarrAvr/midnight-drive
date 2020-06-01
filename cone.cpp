#include "cone.h"

Cone::Cone(float x, float y, float width, float height, int damage_level) : Obstacle(x, y, width, height, damage_level) {
    if (!texture.loadFromFile("C:\\Users\\Barr Avrahamov\\source\\repos\\SFML_Stuff\\SFML_Stuff\\Car game v4\\Construction objects\\traffic cone.png")) {
        throw "Cone Image Not Found";
    }
}

void Cone::makeCrashSound(sf::RenderWindow& window) {
    //need to copy sound here
    std::cout << "cone crash noise" << std::endl;
}