#ifndef OOP_FIGHT_H
#define OOP_FIGHT_H

#include "Player.h"
#include "Constants.h"
#include "Singleton.h"
#include <iostream>

class Fight : public Singleton<Fight> {
public:
    // Singleton: Returns a reference to the single Fight instance
    static Fight& getInstance();

    // Inițialize fight with two players
    void InitializeFight(Player& player1, Player& player2);

    // Updates the fight by processing attacks between the two players
    void Update();

    // Destructor
    ~Fight() = default;

    // Operator<<
    friend std::ostream& operator<<(std::ostream& os, const Fight& fight);

private:
    // Constructor
    Fight();

    friend class Singleton<Fight>;

    Player* player1;
    Player* player2;
};

#endif // OOP_FIGHT_H
