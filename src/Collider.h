#ifndef OOP_COLLIDER_H
#define OOP_COLLIDER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Collider {
public:
    // Constructor and destructor
    explicit Collider(sf::RectangleShape& body_);
    ~Collider();

    // Moves the collider by (dx, dy)
    void Move(float dx, float dy);

    // Returns the position of the collider
    [[nodiscard]] sf::Vector2f GetPosition() const;

    // Returns the half of the size of the collider
    [[nodiscard]] sf::Vector2f GetHalfSize() const;

    // Checks for collision with another collider
    // On collision, if solve collision is true, the direction vector is updated
    // and the push factor is applied. Otherwise, it just returns true.
    bool CheckCollision(Collider other, sf::Vector2f &direction, bool solveCollision, float push=1.0f);

    // Operator<<
    friend std::ostream& operator<<(std::ostream& os, const Collider& collider);

private:
    sf::RectangleShape& body;
};

#endif // OOP_COLLIDER_H
