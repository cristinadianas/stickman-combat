#ifndef OOP_DRAWABLE_H
#define OOP_DRAWABLE_H

#include <SFML/Graphics.hpp>

class Drawable {
public:
    Drawable();
    virtual ~Drawable();

    // Pure virtual function for drawing the object
    virtual void Draw(sf::RenderWindow& window) const = 0;

    // A function to draw a health bar
    virtual void DrawHealthBar(sf::RenderWindow& window) const;
};

#endif //OOP_DRAWABLE_H
