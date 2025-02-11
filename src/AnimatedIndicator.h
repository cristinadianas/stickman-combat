#ifndef OOP_ANIMATEDINDICATOR_H
#define OOP_ANIMATEDINDICATOR_H

#include "Indicator.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class AnimatedIndicator : public Indicator {
public:
    // Constructor and destructor
    AnimatedIndicator(sf::Texture* texture, sf::Vector2i imageCount, float switchTime,
                      sf::Vector2f size, sf::Vector2f position);
    virtual ~AnimatedIndicator();

    // Update the animation
    void Update(float deltaTime);

    // Set the current animation row
    void SetRow(int value);

    // Operator<<
    friend std::ostream& operator<<(std::ostream& os, const AnimatedIndicator& animatedIndicator);

private:
    int row;
    Animation animation;
};

#endif // OOP_ANIMATEDINDICATOR_H

