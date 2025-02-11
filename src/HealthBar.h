#ifndef OOP_HEALTHBAR_H
#define OOP_HEALTHBAR_H

#include "Drawable.h"
#include "AnimatedIndicator.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class HealthBar : public Drawable {
public:
    // Constructor and destructor
    HealthBar(int nrHearts_, sf::Vector2f startPosition_, bool goRight_);
    ~HealthBar() = default;

    // Initializes the health bar with a given texture
    void Initialize(sf::Texture* texture);

    // Updates the health bar's animated hearts
    void Update(float deltaTime);

    // Removes one heart from the health bar
    void DeleteHeart();

    // Returns the number of remaining hearts
    [[nodiscard]] int RemainingHearts() const;

    // Returns true if the player has no more hearts
    [[nodiscard]] bool IsDead() const;

    // Draws the health bar
    void Draw(sf::RenderWindow &window) const override;

    // Operator<<
    friend std::ostream& operator<<(std::ostream& os, const HealthBar& healthBar);

private:
    int nrHearts;
    sf::Vector2f startPosition;
    bool goRight;
    std::vector<AnimatedIndicator> hearts;
};

#endif // OOP_HEALTHBAR_H
