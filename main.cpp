#include <cstdlib>
#include "GameState.h"
#include "Constants.h"
#include "MainMenu.h"
#include "GameOver.h"

namespace cs = constants;

int main()
{
    std::srand(std::time(0));

    while (true)
    {
        auto* menu = new MainMenu();
        bool playGame = menu->startMenu();
        delete menu;
        if (!playGame)
        {
            return 0;
        }

        auto* game = new GameState();
        auto gameResult = game->runGame();
        delete game;
        switch (gameResult)
        {
            case GameState::GameResult::RAGEQUIT:
                continue;
            case GameState::GameResult::DIED:
            {
                auto* gm = new GameOver();
                gm->startGameOver();
                delete gm;
                break;
            }
        }
    }
}
