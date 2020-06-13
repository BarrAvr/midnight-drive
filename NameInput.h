#include "Screen.h"
#include <sstream>
#include <fstream>

class NameInput : public virtual Screen
{
private:
    bool continueSelected{};
    sf::Text textbox;
    std::ostringstream text;
    std::vector<sf::Text> line;

public:
    using Score = std::pair<int, std::string>;

    NameInput();

    void draw(sf::RenderWindow& window) override;

    void hoverSelected(int selection) override;

    void inputLogic(int charTyped);

    void deleteLastChar();

    void typedOn(sf::Event input);

    Score addScoreToFile(std::ostream& file);

    std::string getName();

    bool getContinueSelected() const
    { return continueSelected; }
};

