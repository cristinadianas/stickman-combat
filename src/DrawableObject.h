#ifndef OOP_DRAWABLEOBJECT_H
#define OOP_DRAWABLEOBJECT_H

#include <SFML/Graphics.hpp>

class DrawableObject {
public:
    DrawableObject();
    virtual ~DrawableObject();

    // Pure virtual function for drawing the object
    virtual void Draw(sf::RenderWindow& window) const = 0;
};

#endif //OOP_DRAWABLEOBJECT_H
