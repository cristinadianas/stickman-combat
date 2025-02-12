#ifndef OOP_HEALTHBAR_H
#define OOP_HEALTHBAR_H

#include "DrawableObject.h"
#include "AnimatedIndicator.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

template<typename IndicatorType=AnimatedIndicator>
class HealthBar : public DrawableObject {
public:
    // Constructor and destructor
    HealthBar(int nrHearts_, sf::Vector2f startPosition_, bool goRight_)
            : nrHearts(nrHearts_), startPosition(startPosition_), goRight(goRight_)
    {
    };
    ~HealthBar() override = default;

    // Initializes the health bar with a given texture
    void Initialize(sf::Texture* texture) {
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

    // Returns indicator
    IndicatorType& GetIndicator(int index) {
        return hearts.at(index);
    }

    // Updates the health bar's animated hearts
    void Update(float deltaTime) {
        for (int i = 0; i < nrHearts; i++)
            hearts[i].Update(deltaTime);
    }

    // Removes one heart from the health bar
    void DeleteHeart() {
        if (!IsDead()) {
            hearts.pop_back();
            nrHearts--;
        }
    }

    // Removes one heart from the health bar
    int RemainingHearts() const {
        return nrHearts;
    }

    // Returns true if the player has no more hearts
    bool IsDead() const {
        return nrHearts <= 0;
    }

    // Draws the health bar
    void Draw(sf::RenderWindow &window) const override{
        for (int i = 0; i < nrHearts; i++)
            hearts[i].Draw(window);
    }

    // Operator<<
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const HealthBar<U>& healthBar);

private:
    int nrHearts;
    sf::Vector2f startPosition;
    bool goRight;
    // Could be of type Indicator instead of AnimatedIndicator in case
    // we don't want this health bar to run animations
    std::vector<IndicatorType> hearts;
};

template<typename IndicatorType>
std::ostream& operator<<(std::ostream& os, const HealthBar<IndicatorType>& healthBar) {
    os << "Remaining hearts: " << healthBar.nrHearts << "\n";
    return os;
}

#endif // OOP_HEALTHBAR_H
