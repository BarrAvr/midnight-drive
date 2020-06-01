#include <iostream>
#include <SFML/Graphics.hpp>
#include "obstacle.h"
#include "Car.h"
#include "baracade.h"
#include "gasoline.h"
#include "cone.h"

using namespace std;

bool checkCollisions(Car, Obstacle*);

//coin obstacle

using namespace sf;
using namespace obs;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Obstacle Testing");
    sf::Texture texture;
    if (!texture.loadFromFile("C:\\Users\\Barr Avrahamov\\source\\repos\\SFML_Stuff\\SFML_Stuff\\Car game v4\\Construction objects\\Traffic cone.png")) {
        window.close();
    }

    window.getSize().x;

    Obstacle* ptr;

    ptr = new Baracade(0, 0, 120, 120);

    Car car(120, 0, 120, 120);

    while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (ptr != nullptr && Obstacle::checkCollisions(car, ptr)) {
                cout << "Health: " << car.getHealth() << endl;
                dynamic_cast<Baracade*>(ptr)->crashInToCar(window, car);
                delete ptr;
                ptr = nullptr;
                cout << "Health: " << car.getHealth() << endl;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                car.move(1, 0);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                car.move(-1, 0);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                car.move(0, -1);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                car.move(0, 1);
            }

            window.clear();
            if (ptr != nullptr) {
                (*ptr).draw(window);
            }
            car.draw(window);
            window.display();
    }

    return 0;
}