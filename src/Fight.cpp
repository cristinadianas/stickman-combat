#include "Fight.h"

Fight::Fight(Player& player1, Player& player2)
        : player1(player1), player2(player2) {
}

void Fight::Update() {
    if (player1.IsInAttackingPhase2()) {
        if (player2.IsAttackable() && player2.IsInAttackRange(player1)) {
            player1.ExecuteAttack();
            player2.TakeHit();
        }
    }
    if (player2.IsInAttackingPhase2()) {
        if (player1.IsAttackable() && player1.IsInAttackRange(player2)) {
            player2.ExecuteAttack();
            player1.TakeHit();
        }
    }

    if (player1.IsDead()) {
        player2.Wins();
    }
    else if (player2.IsDead()) {
        player1.Wins();
    }
}

std::ostream& operator<<(std::ostream& os, const Fight& fight) {
    os << "---Fight between---\n\n";

    os << "Player 1:\n" << fight.player1 << "\n";
    os << "Player 2:\n" << fight.player2 << "\n";

    return os;
}
