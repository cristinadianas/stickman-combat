#ifndef OOP_ANIMATION_H
#define OOP_ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameExceptions.h"

class Animation {
public:
    // Constructor and destructor
    Animation(sf::Texture* texture, sf::Vector2i imageCount, float switchTime, bool repeat=true);
    ~Animation();

    // Getter for the current UV rectangle
    [[nodiscard]] sf::IntRect GetUVRect() const;

    // Updates the animation frame based on the row and elapsed time
    void Update(int row, float deltaTime, bool faceRight=true);

    // Operator<<
    friend std::ostream& operator<<(std::ostream& os, const Animation& animation);

private:
    sf::Vector2i imageCount;
    sf::Vector2i currentImage;
    sf::IntRect uvRect;
    float totalTime;
    float switchTime;
    bool repeat;
    bool finished;
};

#endif // OOP_ANIMATION_H

