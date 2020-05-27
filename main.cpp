#include "GameState.h"

int main()
{
    std::srand(std::time(0));
    GameState game = GameState();
    game.runGame();
    return 0;
}
