#ifndef OOP_PLATFORM_H
#define OOP_PLATFORM_H

#include "Indicator.h"
#include "Collider.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Platform : public Indicator {
public:
    // Constructor and destructor
    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    ~Platform() override;

    // Returns a Collider
    Collider GetCollider();

    // Operator<<
    friend std::ostream& operator<<(std::ostream& os, const Platform& platform);
};

#endif // OOP_PLATFORM_H
