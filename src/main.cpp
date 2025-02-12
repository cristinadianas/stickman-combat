#include <iostream>
#include <array>
#include <thread>
#include "Constants.h"
#include "GameExceptions.h"
#include "Game.h"


int main() {
    try {
        Game game(player1Name, player2Name);
        game.Run();
        return 0;
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
