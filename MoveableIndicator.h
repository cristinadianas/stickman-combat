#ifndef OOP_MOVEABLE_INDICATOR_H
#define OOP_MOVEABLE_INDICATOR_H

#include "Indicator.h"

class MoveableIndicator : public Indicator {
public:
    // Constructor and destructor
    MoveableIndicator(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    virtual ~MoveableIndicator();

    // Moves the indicator by (dx, dy).
    void Move(float dx, float dy);

    // Sets the scale
    void SetScale(const sf::Vector2f& scale);

    // Sets the position
    void SetPosition(const sf::Vector2f& position);

    // Returns the current position
    sf::Vector2f GetPosition() const;
};

#endif // OOP_MOVEABLE_INDICATOR_H

