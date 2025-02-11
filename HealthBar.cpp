#include "HealthBar.h"

HealthBar::HealthBar(int nrHearts_, sf::Vector2f startPosition_, bool goRight_)
        : nrHearts(nrHearts_), startPosition(startPosition_), goRight(goRight_)
{
}

void HealthBar::Initialize(sf::Texture* texture) {
    sf::Vector2f coordinates;
    coordinates.y = startPosition.y;

    for (int i = 0; i < nrHearts; i++) {
        if (goRight)
            coordinates.x = startPosition.x + (HEART_SIZE * (float) i);
        else
            coordinates.x = startPosition.x - (HEART_SIZE * (float) i);

        hearts.emplace_back(
                texture,
                imageCountHeart,
                SWITCHTIME_HEART,
                sf::Vector2f(HEART_SIZE, HEART_SIZE),
                coordinates
        );
    }
}

void HealthBar::Update(float deltaTime) {
    if (nrHearts == 1)
        hearts[0].SetRow(LAST_HEART);

    for (int i = 0; i < nrHearts; i++)
        hearts[i].Update(deltaTime);
}

void HealthBar::DeleteHeart() {
    if (!IsDead()) {
        hearts.pop_back();
        nrHearts--;
    }
}

int HealthBar::RemainingHearts() const {
    return nrHearts;
}

bool HealthBar::IsDead() const {
    return nrHearts <= 0;
}

void HealthBar::Draw(sf::RenderWindow &window) const {
    for (int i = 0; i < nrHearts; i++)
        hearts[i].Draw(window);
}

std::ostream& operator<<(std::ostream& os, const HealthBar& healthBar) {
    os << "Remaining hearts: " << healthBar.nrHearts << "\n";
    return os;
}

