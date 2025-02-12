#include <iostream>
#include <array>
#include <thread>
#include "GameExceptions.h"
#include "Game.h"


int main() {
    try {
        Game::getInstance(player1Name, player2Name).Run();
    }

    catch (const GameException &e) {
        std::cerr << "Game Exception: " << e.what() << "\n";
        return -1;
    }

    catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
        return -2;
    }
}
