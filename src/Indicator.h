#ifndef OOP_INDICATOR_H
#define OOP_INDICATOR_H

#include "DrawableObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Indicator : public DrawableObject {
public:
    Indicator(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);

    ~Indicator() override;

    // Overridde draw function
    void Draw(sf::RenderWindow &window) const override;

    // Operator<<
    friend std::ostream& operator<<(std::ostream& os, const Indicator& indicator);

protected:
    sf::RectangleShape body;
};

#endif // OOP_INDICATOR_H
