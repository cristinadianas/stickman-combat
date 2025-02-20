#ifndef OOP_HEALTHBAR_H
#define OOP_HEALTHBAR_H

#include "DrawableObject.h"
#include "AnimatedIndicator.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class HealthBar : public DrawableObject {
public:
    // Constructor and destructor
    HealthBar(int nrHearts_, sf::Vector2f startPosition_, bool goRight_);
    ~HealthBar() override = default;

    // Initializes the health bar with a given texture
    void Initialize(sf::Texture* texture);

    // Returns indicator
    AnimatedIndicator& GetIndicator(int index);

    // Updates the health bar's animated hearts
    void Update(float deltaTime);

    // Removes one heart from the health bar
    void DeleteHeart();

    // Removes one heart from the health bar
    int RemainingHearts() const;

    // Returns true if the player has no more hearts
    bool IsDead() const;

    // Resets the health
    void ResetHealthBar(HealthBar& newHealthBar, sf::Texture* texture, int nrHearts, sf::Vector2f startPosition, bool goRight);

    // Draws the health bar
    void Draw(sf::RenderWindow &window) const override;

private:
    int nrHearts;
    sf::Vector2f startPosition;
    bool goRight;
    std::vector<AnimatedIndicator> hearts;
};

#endif // OOP_HEALTHBAR_H
