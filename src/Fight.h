#ifndef OOP_FIGHT_H
#define OOP_FIGHT_H

#include "Player.h"
#include "GameExceptions.h"
#include "Constants.h"
#include <SFML/Audio.hpp>
#include <iostream>

class Fight {
public:
    // Constructor and destructor
    Fight(Player& player1, Player& player2);
    ~Fight() = default;

    // Updates the fight by processing attacks between the two players
    void Update();

    // Operator<<
    friend std::ostream& operator<<(std::ostream& os, const Fight& fight);

private:
    sf::Music hitSound;
    Player& player1;
    Player& player2;
};

#endif // OOP_FIGHT_H
