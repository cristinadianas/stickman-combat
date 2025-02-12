#include "Fight.h"

Fight::Fight(Player& player1, Player& player2)
        : player1(player1), player2(player2) {
}

void Fight::Update() {
    if (player1.IsInAttackingPhase2()) {
        if (player2.IsAttackable() && player2.IsInAttackRange(player1)) {
            player1.ExecuteAttack();
            audioResources.GetHitSound().play();
            player2.TakeHit();
        }
    }
    if (player2.IsInAttackingPhase2()) {
        if (player1.IsAttackable() && player1.IsInAttackRange(player2)) {
            player2.ExecuteAttack();
            audioResources.GetHitSound().play();
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
    os << "Fight between " << fight.player1.GetName().toAnsiString() << " and "
       << fight.player2.GetName().toAnsiString() << "! ";

    if (fight.player1.RemainingHearts() > fight.player2.RemainingHearts())
        os << fight.player1.GetName().toAnsiString() << " is more likely to win!";
    else if (fight.player1.RemainingHearts() < fight.player2.RemainingHearts())
        os << fight.player2.GetName().toAnsiString() << " is more likely to win!";
    else os << "Equal chances to win!\n";

    return os;
}
